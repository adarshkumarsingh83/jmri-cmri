package com.adarsh.model.trains.service;

import lombok.extern.slf4j.Slf4j;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.MqttPersistenceException;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.integration.dsl.IntegrationFlow;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHeaders;
import org.springframework.stereotype.Service;

import java.util.Collections;

@Slf4j
@Service
public class MQTTPublishService {

    @Autowired
    MqttClient mqttClient;

   /* @Autowired
    private IntegrationFlow mqttOutboundFlow;

    public void publishDataToMqtt(final String data) {
        mqttOutboundFlow.getInputChannel().send(new Message<String>() {

            @Override
            public String getPayload() {
                return data;
            }

            @Override
            public MessageHeaders getHeaders() {
                return new MessageHeaders(Collections.EMPTY_MAP);
            }
        });
    }*/

    public void publish(final String topic, final String payload, int qos, boolean retained)
            throws MqttPersistenceException, MqttException {
        MqttMessage mqttMessage = new MqttMessage();
        mqttMessage.setPayload(payload.getBytes());
        mqttMessage.setQos(qos);
        mqttMessage.setRetained(retained);
        mqttClient.publish(topic, mqttMessage);
        //mqttClient.disconnect();
    }

}
