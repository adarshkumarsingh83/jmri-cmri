package com.adarsh.model.trains.service;

import lombok.extern.slf4j.Slf4j;
import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttMessage;

@Slf4j
public class PushCallback implements MqttCallbackExtended {

    /**
     * Process the received message here.
     *
     * @param s message subject
     * @param mqttMessage message object
     * @throws Exception
     */
    @Override
    public void messageArrived(String s, MqttMessage mqttMessage) throws Exception {
        // The message after the subscription is executed here
        String payload = new String(mqttMessage.getPayload());
        log.info("main content: [{}]", s, payload);
    }

    /**
     * Called when receiving the delivery token of the QoS 1 or QoS 2 message that has been issued.
     *
     * @param iMqttDeliveryToken delivery token of the message
     */
    @Override
    public void deliveryComplete(IMqttDeliveryToken iMqttDeliveryToken) {
        log.info("Sending completed?--->[{}]", iMqttDeliveryToken.isComplete());
    }

    /**
     * This method is called after the client connection is disconnected
     *
     * @param throwable
     */
    @Override
    public void connectionLost(Throwable throwable) {
        log.error("Disconnected, you can reconnect...");
    }

    /**
     * This method is called after the client connection is successful
     *
     * @param b
     * @param s
     */
    @Override
    public void connectComplete(boolean b, String s) {
        log.error("Connection is successful...");
    }

}
