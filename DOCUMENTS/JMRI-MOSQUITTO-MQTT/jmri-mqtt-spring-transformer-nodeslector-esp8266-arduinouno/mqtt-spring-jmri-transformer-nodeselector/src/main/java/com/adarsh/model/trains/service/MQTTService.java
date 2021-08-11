package com.adarsh.model.trains.service;

import com.adarsh.model.trains.beans.MqttProperties;
import com.adarsh.model.trains.beans.NodeConfigurations;
import com.adarsh.model.trains.util.CircularQueue;
import lombok.extern.slf4j.Slf4j;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import javax.annotation.PostConstruct;
import java.util.HashMap;
import java.util.Map;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@Service
public class MQTTService {

    final public static Map<String, CircularQueue<String>> store = new HashMap<>();
    final public static String ON = "ON";
    final public static String OFF = "OF";
    final public static String TH = "TH";
    final public static String CL = "CL";
    final public static String LIGHT = "LIGHT";
    final public static String THROWN = "THROWN";
    final public static String CLOSE = "CLOSE";
    final public static String SIGNAL = "SIGNAL";
    final public static String TURNOUT = "TURNOUT";

    @Value("${amt.mqtt.transform.publish}")
    Boolean transformationPublish;

    @Value("${amt.mqtt.transform.endpoints.enabled}")
    Boolean transformationEndpointsEnabled;

    @Value("${amt.mqtt.transform.endpoints.store.size}")
    Integer storeSize;

    @Autowired
    MqttClient mqttClient;

    @Autowired
    MqttProperties properties;

    @Autowired
    NodeConfigurations nodeConfigurations;

    @PostConstruct
    public void init() {
        nodeConfigurations.getNodes().stream().forEach(node -> {
            store.put(node.getNodeId(), new CircularQueue<String>(storeSize));
        });
    }

    public void transformData(String mqttTopic, String status) throws Exception {
        if (!mqttTopic.isEmpty()) {
            if (mqttTopic.startsWith(properties.getLightTopic())) {
                Integer numberVar = Integer.parseInt(mqttTopic.replace(properties.getLightTopic(), ""));
                //  to find out the node and then push the data to that topic
                NodeConfigurations.Nodes node = this.getNode(LIGHT, numberVar);

                status = (status.equalsIgnoreCase(ON) ? ON : OFF);
                status = this.nodeWiseDataGenerated(LIGHT, node, numberVar, status);
                if (transformationPublish) {
                    this.publish(properties.getTopicPub() + node.getNodeId() + "/light/" + numberVar, status, 1, false);
                }
                if (transformationEndpointsEnabled) {
                    store.get(node.getNodeId()).enqueue(status);
                }

            } else if (mqttTopic.startsWith(properties.getTurnoutTopic())) {
                Integer numberVar = Integer.parseInt(mqttTopic.replace(properties.getTurnoutTopic(), ""));
                if (numberVar >= nodeConfigurations.getTurnoutStartingAddress()
                        && numberVar < nodeConfigurations.getSignalStartingAddress()) {
                    //  to find out the node and then push the data to that node topic
                    NodeConfigurations.Nodes node = this.getNode(TURNOUT, numberVar);
                    status = (status.equalsIgnoreCase(THROWN) ? TH : CL);
                    status = this.nodeWiseDataGenerated(TURNOUT, node, numberVar, status);
                    if (transformationPublish) {
                        this.publish(properties.getTopicPub() + node.getNodeId() + "/turnout/" + numberVar, status, 1, false);
                    }
                    if (transformationEndpointsEnabled) {
                        store.get(node.getNodeId()).enqueue(status);
                    }
                } else {
                    //  to find out the node and then push the data to that node topic
                    NodeConfigurations.Nodes node = this.getNode(SIGNAL, numberVar);
                    status = (status.equalsIgnoreCase(THROWN) ? ON : OFF);
                    status = this.nodeWiseDataGenerated(SIGNAL, node, numberVar, status);
                    if (transformationPublish) {
                        this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/" + numberVar, status, 1, false);
                    }
                    if (transformationEndpointsEnabled) {
                        store.get(node.getNodeId()).enqueue(status);
                    }
                }
            } else if (mqttTopic.startsWith(properties.getSignalTopic())) {
                //  to find out the node and then push the data to that node topic
                Integer numberVar = Integer.parseInt(mqttTopic.replace(properties.getSignalTopic(), ""));
                NodeConfigurations.Nodes node = this.getNode(SIGNAL, numberVar);
                status = (status.equalsIgnoreCase(ON) ? ON : OFF);
                status = this.nodeWiseDataGenerated(SIGNAL, node, numberVar, status);
                if (transformationPublish) {
                    this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/" + numberVar, status, 1, false);
                }
                if (transformationEndpointsEnabled) {
                    store.get(node.getNodeId()).enqueue(status);
                }
            }
        }
    }

    private NodeConfigurations.Nodes getNode(String type, Integer number) {
        return nodeConfigurations.getNodes().stream().filter(e -> {
            if (type.equalsIgnoreCase(LIGHT)) {
                if (e.getLightStartAddress() != null && e.getLightStartAddress() != 0
                        && e.getLightCount() != null && e.getLightCount() != 0) {
                    return number >= e.getLightStartAddress()
                            && number <= e.getLightStartAddress() + e.getLightCount() ? true : false;
                } else {
                    return false;
                }
            } else if (type.equalsIgnoreCase(TURNOUT)) {
                if (e.getTurnoutStartAddress() != null && e.getTurnoutStartAddress() != 0
                        && e.getTurnoutCount() != null && e.getTurnoutCount() != 0) {
                    return number >= e.getTurnoutStartAddress() && number <= e.getTurnoutStartAddress() + e.getTurnoutCount() ? true : false;
                } else {
                    return false;
                }
            } else if (type.equalsIgnoreCase(SIGNAL)) {
                if (e.getSignalStartAddress() != null && e.getSignalStartAddress() != 0
                        && e.getSignalCount() != null && e.getSignalCount() != 0) {
                    return number >= e.getSignalStartAddress() && number <= e.getSignalStartAddress() + e.getSignalCount() ? true : false;
                } else {
                    return false;
                }
            } else
                return false;
        }).findFirst().get();
    }

    private String findBoardPin(NodeConfigurations.Nodes node, Integer pinNo, String state) {
        String data = "";
        int pin = pinNo - 1;
        int board = (pin / 16);
        if (board <= node.getTurnoutBoardCount() + node.getLightBoardCount()
                && pin <= (node.getTurnoutBoardCount() + node.getLightBoardCount()) * 16) {
            int totalPins = (board * 16);
            pin = (pin - totalPins);
            pin = (pin == -1) ? 0 : pin;
            data = (board < 10 ? "0" + board : board) + ":" + (pin < 10 ? "0" + pin : pin) + ":" + state;
        }
        return data;
    }


    public String nodeWiseDataGenerated(String type, NodeConfigurations.Nodes node, Integer inputPin, String state) {
        System.out.print(inputPin + ":");
        if (type.equals(TURNOUT)) {
            inputPin = (inputPin - node.getTurnoutStartAddress());
            inputPin = (inputPin * 2);
            if (state.equals(TH)) {
                inputPin = inputPin - 1;
            }
            // todo find board and pin for the turnout based on configuration
            return this.findBoardPin(node, inputPin, state);
        } else if (type.equals(SIGNAL)) {
            inputPin = (inputPin - node.getSignalStartAddress()) + (node.getTurnoutBoardCount() * 16);
            // todo find board and pin for the signal based on configuration
            return this.findBoardPin(node, inputPin, state);
        } else if (type.equals(LIGHT)) {
            inputPin = (inputPin - node.getLightStartAddress()) + (node.getTurnoutBoardCount() * 16) + node.getSignalCount();
            // todo find board and pin for the light based on configuration
            return this.findBoardPin(node, inputPin, state);
        }
        return null;
    }

    public void publish(final String topic, final String payload, int qos, boolean retained)
            throws MqttException {
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setPayload(payload.getBytes());
        mqttMessage.setQos(qos);
        mqttMessage.setRetained(retained);
        mqttClient.publish(topic, mqttMessage);
    }

    public String getData(String nodeId) throws Exception {
        return store.get(nodeId).dequeue();
    }
}
