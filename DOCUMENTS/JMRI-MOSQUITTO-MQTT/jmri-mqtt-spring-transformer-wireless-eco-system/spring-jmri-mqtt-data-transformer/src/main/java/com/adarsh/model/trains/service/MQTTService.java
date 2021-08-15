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
    final public static List<String> cache2 = new LinkedList<>();
    final public static List<String> cache3 = new LinkedList<>();
    final public static String EMPTY = "";
    final public static String COLLEN = ":";
    final public static String CONNECTION = "|";
    final public static String ZERO = "0";
    final public static String LIGHT_PREFIX = "L:0";
    final public static String TURNOUT_PREFIX = "T:";
    final public static String SIGNAL_PREFIX = "S:";
    final public static String ON = "ON";
    final public static String OFF = "OF";
    final public static String TH = "TH";
    final public static String CL = "CL";
    final public static String THROWN = "THROWN";
    final public static String CLOSED = "CLOSED";
    final public static String LIGHT = "LIGHT";
    final public static String SIGNAL = "SIGNAL";
    final public static String TURNOUT = "TURNOUT";


    @Value("${amt.mqtt.transform.endpoints.enabled}")
    Boolean transformationEndpointsEnabled;

    @Autowired
    MqttClient mqttClient;

    @Autowired
    MqttProperties properties;

    @Autowired
    NodeConfigurations nodeConfigurations;

    @PostConstruct
    public void init() {
        if (transformationEndpointsEnabled) {
            nodeConfigurations.getNodes().stream().forEach(node -> {
                log.debug("Api Endpoint Cache Enabled node= {} with size={} ", node.getNodeId(), node.getApiEndpointCacheSize());
                store.put(node.getNodeId(), new CircularQueue<String>(node.getApiEndpointCacheSize()));
            });
        }
    }

    public void transformData(String mqttTopic, String jmriState) throws Exception {
        log.debug("Mqtt transformData mqttTopic= {} with jmriState={} ", mqttTopic, jmriState);
        try {
            if (!mqttTopic.isEmpty()) {
                if (mqttTopic.startsWith(properties.getLightTopic())) {
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getLightTopic(), EMPTY));
                    if (jmriId >= nodeConfigurations.getLightStartingAddress()
                            && jmriId < nodeConfigurations.getTurnoutStartingAddress()) {
                        this.processLight(jmriId, jmriState);
                    } else {
                        log.error("JmriId for Light Type is not Valid Id={} which is defined in Configuration", jmriId);
                        this.publish(properties.getErrorTopic(), "Invalid jmriid for light type " + jmriId, 1, false);
                    }
                } else if (mqttTopic.startsWith(properties.getTurnoutTopic())) {
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getTurnoutTopic(), EMPTY));
                    if (jmriId >= nodeConfigurations.getTurnoutStartingAddress()
                            && jmriId < nodeConfigurations.getSignal2LStartingAddress()) {
                        this.processTurnout(jmriId, jmriState);
                    } else if (jmriId >= nodeConfigurations.getSignal2LStartingAddress()) {
                        this.processSignal(jmriId, jmriState);
                    } else {
                        log.error("JmriId for Turnout|Signals Type is not Valid Id={} which is defined in Configuration", jmriId);
                        this.publish(properties.getErrorTopic(), "Invalid jmriid for turnout|signal type " + jmriId, 1, false);
                    }
                } else if (mqttTopic.startsWith(properties.getSignalTopic())) {
                    Integer jmriId = Integer.parseInt(mqttTopic.replace(properties.getSignalTopic(), EMPTY));
                    if (jmriId >= nodeConfigurations.getSignal2LStartingAddress()) {
                        this.processSignal(jmriId, jmriState);
                    } else {
                        log.error("JmriId for Signals Type is not Valid Id={} which is defined in Configuration", jmriId);
                        this.publish(properties.getErrorTopic(), "Invalid jmriid for signal type " + jmriId, 1, false);
                    }
                }
            }
        } catch (Exception e) {
            this.publish(properties.getErrorTopic(), mqttTopic + COLLEN + jmriState, 1, false);
            log.error("Exception while data transformation  mqttTopic= {} with jmriState={} exception={}", mqttTopic, jmriState, e);
        }
    }

    private void processSignal(Integer jmriId, String jmriState) throws Exception {
        log.debug("processSignal jmriId= {} with jmriState={} ", jmriId, jmriState);

        //  to find out the node and then push the data to that node topic
        NodeConfigurations.Nodes node = this.getNode(SIGNAL, jmriId);

        if (node != null) {
            if (jmriState.contains(THROWN) || jmriState.contains(CLOSED)) {
                jmriState = (jmriState.equalsIgnoreCase(THROWN) ? ON : OFF);
            } else {
                jmriState = (jmriState.equalsIgnoreCase(ON) ? ON : OFF);
            }
            jmriState = this.nodeWiseDataGenerated(SIGNAL, node, jmriId, jmriState);
            if (jmriId >= node.getSignal3LStartAddress()) {
                if (cache3.size() < 3) {
                    cache3.add(jmriId + COLLEN + jmriState);
                }
                if (cache3.size() == 3) {

                    String signalData = cache3.stream().distinct().collect(Collectors.joining(CONNECTION));
                    this.publish(node.getSignalPublishTopic(), SIGNAL_PREFIX + signalData, 1, false);

                    if (transformationEndpointsEnabled) {
                        store.get(node.getNodeId()).enqueue(SIGNAL_PREFIX + signalData);
                    }
                    cache3.clear();
                }
            } else if (jmriId >= node.getSignal2LStartAddress()) {
                if (cache2.size() < 2) {
                    cache2.add(jmriId + COLLEN + jmriState);
                }
                if (cache2.size() == 2) {

                    String signalData = cache2.stream().distinct().collect(Collectors.joining(CONNECTION));
                    this.publish(node.getSignalPublishTopic(), SIGNAL_PREFIX + signalData, 1, false);

                    if (transformationEndpointsEnabled) {
                        store.get(node.getNodeId()).enqueue(SIGNAL_PREFIX + signalData);
                    }
                    cache2.clear();
                }
            } else {
                this.publish(node.getSignalPublishTopic(), SIGNAL_PREFIX + jmriId + COLLEN + jmriState, 1, false);
                if (transformationEndpointsEnabled) {
                    store.get(node.getNodeId()).enqueue(SIGNAL_PREFIX + jmriId + COLLEN + jmriState);
                }
            }
        } else {
            log.info("Node not found for Signal jmriId= {} jmriState {}", jmriId, jmriState);
            this.publish(properties.getErrorTopic(), "Node not Found for Signal " + jmriId + " state " + jmriState, 1, false);
        }
    }

    private void processTurnout(Integer jmriId, String jmriState) throws Exception {
        log.debug("processTurnout jmriId= {} with jmriState={} ", jmriId, jmriState);
        //  to find out the node and then push the data to that node topic
        NodeConfigurations.Nodes node = this.getNode(TURNOUT, jmriId);
        if (node != null) {
            jmriState = (jmriState.equalsIgnoreCase(THROWN) ? TH : CL);
            jmriState = this.nodeWiseDataGenerated(TURNOUT, node, jmriId, jmriState);
            this.publish(node.getTurnoutPublishTopic(), TURNOUT_PREFIX + jmriId + COLLEN + jmriState, 1, false);
            if (transformationEndpointsEnabled) {
                store.get(node.getNodeId()).enqueue(TURNOUT_PREFIX + jmriId + COLLEN + jmriState);
            }
        } else {
            log.info("Node not found for Turnout jmriId= {} jmriState {}", jmriId, jmriState);
            this.publish(properties.getErrorTopic(), "Node not Found for Turnout" + jmriId + " state " + jmriState, 1, false);
        }
    }

    private void processLight(Integer jmriId, String jmriState) throws Exception {
        log.debug("processLight jmriId= {} with jmriState={} ", jmriId, jmriState);
        //  to find out the node and then push the data to that topic
        NodeConfigurations.Nodes node = this.getNode(LIGHT, jmriId);
        if (node != null) {
            jmriState = (jmriState.equalsIgnoreCase(ON) ? ON : OFF);
            jmriState = this.nodeWiseDataGenerated(LIGHT, node, jmriId, jmriState);
            this.publish(node.getLightPublishTopic(), LIGHT_PREFIX + jmriId + COLLEN + jmriState, 1, false);
            if (transformationEndpointsEnabled) {
                store.get(node.getNodeId()).enqueue(LIGHT_PREFIX + jmriId + COLLEN + jmriState);
            }
        } else {
            log.info("Node not found for Light jmriId= {} jmriState {}", jmriId, jmriState);
            this.publish(properties.getErrorTopic(), "Node not Found for Light" + jmriId + " state " + jmriState, 1, false);
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
                if (jmriId >= e.getSignal3LStartAddress()) {
                    if (e.getSignal3LStartAddress() != null && e.getSignal3LStartAddress() != 0
                            && e.getSignal3LCount() != null && e.getSignal3LCount() != 0) {
                        return jmriId >= e.getSignal3LStartAddress() && jmriId <= e.getSignal3LStartAddress() + e.getSignal3LCount() ? true : false;
                    } else {
                        return false;
                    }
                } else if (jmriId >= e.getSignal2LStartAddress() && jmriId < e.getSignal3LStartAddress()) {
                    if (e.getSignal2LStartAddress() != null && e.getSignal2LStartAddress() != 0
                            && e.getSignal2LCount() != null && e.getSignal2LCount() != 0) {
                        return jmriId >= e.getSignal2LStartAddress() && jmriId <= e.getSignal2LStartAddress() + e.getSignal2LCount() ? true : false;
                    } else {
                        return false;
                    }
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
            data = (board < 10 ? ZERO + board : board) + COLLEN + (pin < 10 ? ZERO + pin : pin) + COLLEN + state;
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
            if (jmriId >= node.getSignal3LStartAddress()) {
                jmriId = (jmriId - node.getSignal3LStartAddress()) + (node.getTurnoutBoardCount() * 16);
            } else {
                jmriId = (jmriId - node.getSignal2LStartAddress()) + (node.getTurnoutBoardCount() * 16);
            }
            //  find board and pin for the signal based on configuration
            return this.findBoardPin(node, jmriId, state);
        } else if (type.equals(LIGHT)) {
            jmriId = (jmriId - node.getLightStartAddress())
                    + (node.getTurnoutBoardCount() * 16)
                    + node.getSignal2LCount() + node.getSignal3LCount();
            //  find board and pin for the light based on configuration
            return this.findBoardPin(node, jmriId, state);
        }
        return null;
    }

    public void publish(final String topic, final String payload, int qos, boolean retained)
            throws MqttException {
        log.debug("Publishing to Mqtt after transformation  Topic={}  payload={}", topic, payload);
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