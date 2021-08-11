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
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Slf4j
@Service
public class MQTTService {

    final public static Map<String, CircularQueue<String>> store = new HashMap<>();
    final public static List<String> cache = new LinkedList<>();
    final public static String ON = "ON";
    final public static String OFF = "OF";
    final public static String TH = "TH";
    final public static String CL = "CL";
    final public static String LIGHT = "LIGHT";
    final public static String THROWN = "THROWN";
    final public static String SIGNAL = "SIGNAL";
    final public static String TURNOUT = "TURNOUT";

    @Value("${amt.mqtt.transform.publish}")
    Boolean transformationPublish;

    @Value("${amt.mqtt.transform.endpoints.enabled}")
    Boolean transformationEndpointsEnabled;

    @Value("${amt.mqtt.transform.endpoints.store.size}")
    Integer storeSize;

    @Value("${amt.three.output.signal.joiner}")
    Boolean threeOutputSignalJoiner;

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
        try {

            if (!mqttTopic.isEmpty()) {
                if (mqttTopic.startsWith(properties.getLightTopic())) {
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getLightTopic(), ""));
                    //  to find out the node and then push the data to that topic
                    NodeConfigurations.Nodes node = this.getNode(LIGHT, jmriId);

                    status = (status.equalsIgnoreCase(ON) ? ON : OFF);
                    status = this.nodeWiseDataGenerated(LIGHT, node, jmriId, status);
                    if (transformationPublish) {
                        this.publish(properties.getTopicPub() + node.getNodeId() + "/light/", jmriId + ":" + status, 1, false);
                    }
                    if (transformationEndpointsEnabled) {
                        store.get(node.getNodeId()).enqueue(jmriId + ":" + status);
                    }

                } else if (mqttTopic.startsWith(properties.getTurnoutTopic())) {
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getTurnoutTopic(), ""));
                    if (jmriId >= nodeConfigurations.getTurnoutStartingAddress()
                            && jmriId < nodeConfigurations.getSignalStartingAddress()) {
                        //  to find out the node and then push the data to that node topic
                        NodeConfigurations.Nodes node = this.getNode(TURNOUT, jmriId);
                        status = (status.equalsIgnoreCase(THROWN) ? TH : CL);
                        status = this.nodeWiseDataGenerated(TURNOUT, node, jmriId, status);
                        if (transformationPublish) {
                            this.publish(properties.getTopicPub() + node.getNodeId() + "/turnout/", jmriId + ":" + status, 1, false);
                        }
                        if (transformationEndpointsEnabled) {
                            store.get(node.getNodeId()).enqueue(jmriId + ":" + status);
                        }
                    } else {
                        //  to find out the node and then push the data to that node topic
                        NodeConfigurations.Nodes node = this.getNode(SIGNAL, jmriId);
                        status = (status.equalsIgnoreCase(THROWN) ? ON : OFF);
                        status = this.nodeWiseDataGenerated(SIGNAL, node, jmriId, status);

                        if (threeOutputSignalJoiner) {
                            if (cache.size() < 3) {
                                cache.add(jmriId + ":" + status);
                            }
                            if (cache.size() == 3) {
                                String signalData = cache.stream().collect(Collectors.joining("|"));

                                if (transformationPublish) {
                                    this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/", signalData, 1, false);
                                }
                                if (transformationEndpointsEnabled) {
                                    store.get(node.getNodeId()).enqueue(signalData);
                                }


                                cache.clear();
                            }
                        } else {
                            store.get(node.getNodeId()).enqueue(jmriId + ":" + status);
                        }
                    }
                } else if (mqttTopic.startsWith(properties.getSignalTopic())) {
                    //  to find out the node and then push the data to that node topic
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getSignalTopic(), ""));
                    NodeConfigurations.Nodes node = this.getNode(SIGNAL, jmriId);
                    status = (status.equalsIgnoreCase(ON) ? ON : OFF);
                    status = this.nodeWiseDataGenerated(SIGNAL, node, jmriId, status);
                    if (threeOutputSignalJoiner) {
                        if (cache.size() < 3) {
                            cache.add(jmriId + ":" + status);
                        }
                        if (cache.size() == 3) {
                            String signalData = cache.stream().collect(Collectors.joining("|"));
                            if (transformationPublish) {
                                this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/", signalData, 1, false);
                            }
                            if (transformationEndpointsEnabled) {
                                store.get(node.getNodeId()).enqueue(signalData);
                            }
                            cache.clear();
                        }
                    } else {
                        store.get(node.getNodeId()).enqueue(jmriId + ":" + status);
                    }
                }
            }
        } catch (Exception e) {
            this.publish(properties.getErrorTopic(), mqttTopic + ":" + status, 1, false);
        }
    }

    private NodeConfigurations.Nodes getNode(String type, Integer jmriId) {
        return nodeConfigurations.getNodes().stream().filter(e -> {
            if (type.equalsIgnoreCase(LIGHT)) {
                if (e.getLightStartAddress() != null && e.getLightStartAddress() != 0
                        && e.getLightCount() != null && e.getLightCount() != 0) {
                    return jmriId >= e.getLightStartAddress()
                            && jmriId <= e.getLightStartAddress() + e.getLightCount() ? true : false;
                } else {
                    return false;
                }
            } else if (type.equalsIgnoreCase(TURNOUT)) {
                if (e.getTurnoutStartAddress() != null && e.getTurnoutStartAddress() != 0
                        && e.getTurnoutCount() != null && e.getTurnoutCount() != 0) {
                    return jmriId >= e.getTurnoutStartAddress() && jmriId <= e.getTurnoutStartAddress() + e.getTurnoutCount() ? true : false;
                } else {
                    return false;
                }
            } else if (type.equalsIgnoreCase(SIGNAL)) {
                if (e.getSignalStartAddress() != null && e.getSignalStartAddress() != 0
                        && e.getSignalCount() != null && e.getSignalCount() != 0) {
                    return jmriId >= e.getSignalStartAddress() && jmriId <= e.getSignalStartAddress() + e.getSignalCount() ? true : false;
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


    public String nodeWiseDataGenerated(String type, NodeConfigurations.Nodes node, Integer jmriId, String state) {
        System.out.print(jmriId + ":");
        if (type.equals(TURNOUT)) {
            jmriId = (jmriId - node.getTurnoutStartAddress());
            jmriId = (jmriId * 2);
            if (state.equals(TH)) {
                jmriId = jmriId - 1;
            }
            //  find board and pin for the turnout based on configuration
            return this.findBoardPin(node, jmriId, state);
        } else if (type.equals(SIGNAL)) {
            jmriId = (jmriId - node.getSignalStartAddress()) + (node.getTurnoutBoardCount() * 16);
            //  find board and pin for the signal based on configuration
            return this.findBoardPin(node, jmriId, state);
        } else if (type.equals(LIGHT)) {
            jmriId = (jmriId - node.getLightStartAddress()) + (node.getTurnoutBoardCount() * 16) + node.getSignalCount();
            //  find board and pin for the light based on configuration
            return this.findBoardPin(node, jmriId, state);
        }
        return null;
    }

    public void publish(final String topic, final String payload, int qos, boolean retained)
            throws MqttException {
        log.info("::=>  Topic {}  payload {}", topic, payload);
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
