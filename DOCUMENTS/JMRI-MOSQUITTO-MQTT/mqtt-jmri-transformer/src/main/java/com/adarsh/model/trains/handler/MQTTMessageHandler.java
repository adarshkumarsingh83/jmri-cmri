package com.adarsh.model.trains.handler;

import lombok.extern.slf4j.Slf4j;
import org.springframework.messaging.Message;
import org.springframework.messaging.MessageHandler;
import org.springframework.messaging.MessagingException;
import org.springframework.stereotype.Component;


@Slf4j
@Component
public class MQTTMessageHandler implements MessageHandler {

    private static String topicHeaderName = "mqtt_receivedTopic";

    @Override
    public void handleMessage(Message<?> message) throws MessagingException {
        try {
            String topic = message.getHeaders().get(topicHeaderName) + "";
            log.info("TOPIC " + topic + " Received Message: " + message.getPayload().toString());

            // todo implementation to put back to the proper topic back in mqtt
        } catch (Exception e) {
            log.error(e.getMessage());
        }
    }

}
