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
    final public static String CLOSED = "CLOSED";
    final public static String SIGNAL = "SIGNAL";
    final public static String TURNOUT = "TURNOUT";


    @Value("${amt.mqtt.transform.endpoints.enabled}")
    Boolean transformationEndpointsEnabled;

    @Value("${amt.mqtt.transform.endpoints.store.size}")
    Integer storeSize;

    @Value("${amt.output.signal.joiner}")
    Integer outputSignalJoiner = 0;

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

    public void transformData(String mqttTopic, String jmriState) throws Exception {
        try {

            if (!mqttTopic.isEmpty()) {
                if (mqttTopic.startsWith(properties.getLightTopic())) {
                    processLight(mqttTopic, jmriState);
                } else if (mqttTopic.startsWith(properties.getTurnoutTopic())) {
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getTurnoutTopic(), ""));
                    if (jmriId >= nodeConfigurations.getTurnoutStartingAddress()
                            && jmriId < nodeConfigurations.getSignalStartingAddress()) {
                        processTurnout(jmriId, jmriState);
                    } else {
                        processSignal(jmriId, jmriState);
                    }
                } else if (mqttTopic.startsWith(properties.getSignalTopic())) {
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getSignalTopic(), ""));
                    processSignal(jmriId, jmriState);
                }
            }
        } catch (Exception e) {
            this.publish(properties.getErrorTopic(), mqttTopic + ":" + jmriState, 1, false);
            log.error("Exception {}", e);
        }
    }

    private void processSignal(Integer jmriId, String jmriState) throws Exception {
        //  to find out the node and then push the data to that node topic
        NodeConfigurations.Nodes node = this.getNode(SIGNAL, jmriId);
        if (jmriState.contains(THROWN) || jmriState.contains(CLOSED)) {
            jmriState = (jmriState.equalsIgnoreCase(THROWN) ? ON : OFF);
        } else {
            jmriState = (jmriState.equalsIgnoreCase(ON) ? ON : OFF);
        }
        jmriState = this.nodeWiseDataGenerated(SIGNAL, node, jmriId, jmriState);
        if (outputSignalJoiner == 3) {
            if (cache.size() < 3) {
                cache.add(jmriId + ":" + jmriState);
            }
            if (cache.size() == 3) {

                String signalData = cache.stream().distinct().collect(Collectors.joining("|"));
                this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/", "S:" + signalData, 1, false);

                if (transformationEndpointsEnabled) {
                    store.get(node.getNodeId()).enqueue("S:" + signalData);
                }
                cache.clear();
            }
        } else if (outputSignalJoiner == 2) {
            if (cache.size() < 2) {
                cache.add(jmriId + ":" + jmriState);
            }
            if (cache.size() == 2) {

                String signalData = cache.stream().distinct().collect(Collectors.joining("|"));
                this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/", "S:" + signalData, 1, false);

                if (transformationEndpointsEnabled) {
                    store.get(node.getNodeId()).enqueue("S:" + signalData);
                }
                cache.clear();
            }
        } else {
            this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/", "S:" + jmriId + ":" + jmriState, 1, false);
            if (transformationEndpointsEnabled) {
                store.get(node.getNodeId()).enqueue("S:" + jmriId + ":" + jmriState);
            }
        }
    }

    private void processTurnout(Integer jmriId, String jmriState) throws Exception {
        //  to find out the node and then push the data to that node topic
        NodeConfigurations.Nodes node = this.getNode(TURNOUT, jmriId);
        jmriState = (jmriState.equalsIgnoreCase(THROWN) ? TH : CL);
        jmriState = this.nodeWiseDataGenerated(TURNOUT, node, jmriId, jmriState);
        this.publish(properties.getTopicPub() + node.getNodeId() + "/turnout/", "T:" + jmriId + ":" + jmriState, 1, false);
        if (transformationEndpointsEnabled) {
            store.get(node.getNodeId()).enqueue("T:" + jmriId + ":" + jmriState);
        }
    }

    private void processLight(String mqttTopic, String jmriState) throws Exception {
        Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getLightTopic(), ""));
        //  to find out the node and then push the data to that topic
        NodeConfigurations.Nodes node = this.getNode(LIGHT, jmriId);

        jmriState = (jmriState.equalsIgnoreCase(ON) ? ON : OFF);
        jmriState = this.nodeWiseDataGenerated(LIGHT, node, jmriId, jmriState);
        this.publish(properties.getTopicPub() + node.getNodeId() + "/light/", "L:" + jmriId + ":" + jmriState, 1, false);
        if (transformationEndpointsEnabled) {
            store.get(node.getNodeId()).enqueue("L:" + jmriId + ":" + jmriState);
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
