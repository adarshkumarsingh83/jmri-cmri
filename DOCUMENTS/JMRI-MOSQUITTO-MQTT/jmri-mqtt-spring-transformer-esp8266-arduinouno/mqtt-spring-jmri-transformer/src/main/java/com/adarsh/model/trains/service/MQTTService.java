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

    private final static Map<String, CircularQueue<String>> store = new HashMap<>();
    private final static String ON = "ON";
    private final static String OFF = "OF";
    private final static String THROWN = "THROWN";
    private final static String LIGHT = "LIGHT";
    private final static String SIGNAL = "SIGNAL";
    private final static String TURNOUT = "TURNOUT";
    private final static String MQTT_TOPIC_LIGHT = "/trains/track/light/";
    private final static String MQTT_TOPIC_TURNOUT = "/trains/track/turnout/";
    private final static String MQTT_TOPIC_SIGNAL_HEAD = "/trains/track/signalhead/";

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
            if (mqttTopic.startsWith(MQTT_TOPIC_LIGHT)) {
                Integer numberVar = Integer.parseInt(mqttTopic.replace(MQTT_TOPIC_LIGHT, ""));
                //  to find out the node and then push the data to that topic
                NodeConfigurations.Nodes node = this.getNode(LIGHT, numberVar);
                status = (status.equalsIgnoreCase(ON) ? ON : OFF);
                if (transformationPublish) {
                    this.publish(properties.getTopicPub() + node.getNodeId() + "/light/" + numberVar, status, 1, false);
                }
                if (transformationEndpointsEnabled) {
                    store.get(node.getNodeId()).enqueue("L" + ":" + numberVar + ":" + status);
                }
            } else if (mqttTopic.startsWith(MQTT_TOPIC_TURNOUT)) {
                Integer numberVar = Integer.parseInt(mqttTopic.replace(MQTT_TOPIC_TURNOUT, ""));
                if (numberVar >= nodeConfigurations.getTurnoutStartingAddress()
                        && numberVar < nodeConfigurations.getSignalStartingAddress()) {
                    //  to find out the node and then push the data to that node topic
                    NodeConfigurations.Nodes node = this.getNode(TURNOUT, numberVar);
                    status = (status.equalsIgnoreCase(THROWN) ? "TH" : "CL");
                    if (transformationPublish) {
                        this.publish(properties.getTopicPub() + node.getNodeId() + "/turnout/" + numberVar, status, 1, false);
                    }
                    if (transformationEndpointsEnabled) {
                        store.get(node.getNodeId()).enqueue("T" + ":" + numberVar + ":" + status);
                    }
                } else {
                    //  to find out the node and then push the data to that node topic
                    NodeConfigurations.Nodes node = this.getNode(SIGNAL, numberVar);
                    status = (status.equalsIgnoreCase(THROWN) ? ON : OFF);
                    if (transformationPublish) {
                        this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/" + numberVar, status, 1, false);
                    }
                    if (transformationEndpointsEnabled) {
                        store.get(node.getNodeId()).enqueue("S" + ":" + numberVar + ":" + status);
                    }
                }
            } else if (mqttTopic.startsWith(MQTT_TOPIC_SIGNAL_HEAD)) {
                //  to find out the node and then push the data to that node topic
                Integer numberVar = Integer.parseInt(mqttTopic.replace(MQTT_TOPIC_SIGNAL_HEAD, ""));
                NodeConfigurations.Nodes node = this.getNode(SIGNAL, numberVar);
                status = (status.equalsIgnoreCase(ON) ? ON : OFF);
                if (transformationPublish) {
                    this.publish(properties.getTopicPub() + node.getNodeId() + "/signal/" + numberVar, status, 1, false);
                }
                if (transformationEndpointsEnabled) {
                    store.get(node.getNodeId()).enqueue("S" + ":" + numberVar + ":" + status);
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
