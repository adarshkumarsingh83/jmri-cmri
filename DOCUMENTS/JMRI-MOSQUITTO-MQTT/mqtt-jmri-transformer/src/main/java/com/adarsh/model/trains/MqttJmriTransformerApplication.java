package com.adarsh.model.trains;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.integration.annotation.IntegrationComponentScan;

@IntegrationComponentScan
@SpringBootApplication
public class MqttJmriTransformerApplication {

	public static void main(String[] args) {
		SpringApplication.run(MqttJmriTransformerApplication.class, args);
	}

}
