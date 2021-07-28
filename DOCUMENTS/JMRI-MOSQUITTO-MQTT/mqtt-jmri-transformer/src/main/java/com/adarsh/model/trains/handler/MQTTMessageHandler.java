package com.adarsh.model.trains.handler;

import com.adarsh.model.trains.beans.MqttProperties;
import com.adarsh.model.trains.beans.NodeConfigurations;
import com.adarsh.model.trains.service.MQTTPublishService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessagingException;
import org.springframework.stereotype.Component;


@Slf4j
@Component
public class MQTTMessageHandler implements MessageHandler {

    final private static String TOPIC_HEADER_NAME = "mqtt_receivedTopic";
    final static private String mqtt_topic_light = "/trains/track/light/";
    final static private String mqtt_topic_turnout = "/trains/track/turnout/";
    final static private String mqtt_topic_signalhead = "/trains/track/signalhead/";
    final static private String THROWN = "THROWN";
    final static private String CLOSED = "CLOSED";
    final static private String ON = "ON";
    final static private String OFF = "OFF";

    @Autowired
    MQTTPublishService mqttPublishService;

    @Autowired
    NodeConfigurations nodeConfigurations;

    @Autowired
    MqttProperties properties;

    @Override
    public void handleMessage(Message<?> message) throws MessagingException {
        try {
            String topic = message.getHeaders().get(TOPIC_HEADER_NAME) + "";
            String data = message.getPayload().toString();
            log.info("TOPIC " + topic + " Received Message: " + data);
            this.transformData(topic, data);
            // todo implementation to put back to the proper topic back in mqtt
        } catch (Exception e) {
            log.error(e.getMessage());
        }
    }


    private void transformData(String mqttTopic, String status) throws Exception {
        if (!mqttTopic.isEmpty()) {
            if (mqttTopic.startsWith(mqtt_topic_light)) {
                Integer numberVar = Integer.parseInt(mqttTopic.replace(mqtt_topic_light, ""));
                //  to find out the node and then push the data to that topic
                NodeConfigurations.Nodes node = this.getNode("L", numberVar);
                mqttPublishService.publish(properties.getTopicPub() + node.getNodeNo() + "/light/" + numberVar, status, 1, false);
            } else if (mqttTopic.startsWith(mqtt_topic_turnout)) {
                Integer numberVar = Integer.parseInt(mqttTopic.replace(mqtt_topic_turnout, ""));
                if (numberVar < 3000) {
                    //  to find out the node and then push the data to that node topic
                    NodeConfigurations.Nodes node = this.getNode("T", numberVar);
                    mqttPublishService.publish(properties.getTopicPub() + node.getNodeNo() + "/turnout/" + numberVar, status, 1, false);
                } else {
                    if (status.equalsIgnoreCase(THROWN)) {
                        status = ON;
                    } else {
                        status = OFF;
                    }
                    //  to find out the node and then push the data to that node topic
                    NodeConfigurations.Nodes node = this.getNode("S", numberVar);
                    mqttPublishService.publish(properties.getTopicPub() + node.getNodeNo() + "/signal/" + numberVar, status, 1, false);
                }
            } else if (mqttTopic.startsWith(mqtt_topic_signalhead)) {
                //  to find out the node and then push the data to that node topic
                Integer numberVar = Integer.parseInt(mqttTopic.replace(mqtt_topic_signalhead, ""));
                NodeConfigurations.Nodes node = this.getNode("S", numberVar);
                mqttPublishService.publish(properties.getTopicPub() + node.getNodeNo() + "/signal/" + numberVar, status, 1, false);
            }
        }
    }

    private NodeConfigurations.Nodes getNode(String type, Integer number) {
        return nodeConfigurations.getNodes().stream().filter(e -> {
            if (type.equalsIgnoreCase("L")) {
                return number >= e.getLightStartAddress() && number <= e.getLightStartAddress() + e.getLightCount() ? true : false;
            } else if (type.equalsIgnoreCase("T")) {
                return number >= e.getTurnoutStartAddress() && number <= e.getTurnoutStartAddress() + e.getTurnoutCount() ? true : false;
            } else if (type.equalsIgnoreCase("S")) {
                return number >= e.getSignalStartAddress() && number <= e.getSignalStartAddress() + e.getSignalCount() ? true : false;
            }
            return false;
        }).findFirst().get();
    }
}
