package com.adarsh.model.trains.beans;

import lombok.Data;
import org.springframework.boot.context.properties.ConfigurationProperties;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Primary;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@Data
@Primary
@Configuration
@ConfigurationProperties(prefix = "mqtt-properties")
public class MqttProperties {
    private String host;
    private String clientId;
    private String username;
    private String password;
    private String topicSub;
    private String topicPub;
    private Boolean cleanSession;
    private Integer connectionTimeout;
    private Integer keepAliveInterval;
    private Boolean automaticReconnect;

}
