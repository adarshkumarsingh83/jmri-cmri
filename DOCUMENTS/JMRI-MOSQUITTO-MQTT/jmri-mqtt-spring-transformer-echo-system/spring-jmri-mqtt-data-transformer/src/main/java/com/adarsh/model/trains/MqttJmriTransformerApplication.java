package com.adarsh.model.trains;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.integration.annotation.IntegrationComponentScan;

/*
 * @author Adarsh
 * @author $LastChangedBy: adarsh $
 * @version $Revision: 0001 $, $Date:: 15/6/20 10:12 AM#$
 */

@IntegrationComponentScan
@SpringBootApplication
public class MqttJmriTransformerApplication {

    public static void main(String[] args) {
        SpringApplication.run(MqttJmriTransformerApplication.class, args);
    }

}
