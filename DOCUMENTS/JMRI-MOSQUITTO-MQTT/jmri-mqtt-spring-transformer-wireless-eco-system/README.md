# JMRI MQTT SPRING TRANSFORMER ESP AND ARDUINO WIRELESS ECO SYSTEM 

> Jmri will push the data to the mqtt topic \
> spring transformer application configured with nodes and its details like no of turnout, no of signals, no of light in the node \
> transformer application will read the data from mqtt topics which is pushed by jmri and transform that data node wise  \
> and push back to the mqtt for specific nodes, also store data in end points cache if enabled for serving data via rest endpoints  \
> node wise topics for each esp8266 node will have only relevant data\
> this will reduce the processing on the esp8266 so that it can handle node specific data properly. \
> esp8266 will read data from mqtt nodewise topic or can direclty make http rest endpoint call to spring application and get the data \
> esp8266 will pass the data to the arduino uno or mega via serial line and arduino will do the rest for signals, turnouts, or lights 


### ASSUMPTIONS 
* ALL LIGHTS WILL START FROM 1000 ONWARDS 
* ALL TURNOUT WILL START FROM 10000 ONWARDS 
* ALL 2LED(RED,GREEN) SIGNAL WILL START FROM 20000 ONWARDS 
* ALL 3LED(RED,YELLOW,GREEN) SIGNAL WILL START FROM 30000 ONWARDS 
* ESP8266 IS WILL PUBLISH AND SUSCRIBE DATA FROM MQTT OR VIA REST ENDPOINTS FROM SPRING APPLICATION 
* ARDUINO WILL EXECUTE THE CMD SEND BY SPRING APPLCATION VIA ESP 
* ARDUINO WILL BE CONNECTED WITH THE CHAIN OF THE PCA9685 BOARD FOR SERVO TURNOUT, SNAPSWTICH FOR TURNOUT FOR LIGHT AND SINGAL LED 


### CONFIGURATIONS STEPS 
* java 8 runtime installation 
* Mqtt installation and start see [MQTT SETUP GUILDE LINK ](MQTT-SETUP-README.md)
* jmri installation and configured with mqtt see [JMRI MQTT CONNECTION SETUP AND TESTING ](JMRI-MQTT-SETUP-README.md)
* spring data transformation application installation and execution details see [SPRING TRANSFORMATOIN APPLICATION ](spring-jmri-mqtt-data-transformer/README.md)
* reading data after transformaton see below section 

---

## FOR LIGHT TURNOUT AND SIGNALS 

### ESP code 

* for reading data directly via mqtt topic using esp8266 
	* [link for configuraiton and deplayment and setup ](esp8266-transformation-mqtt-client/README.md)		
* for reading data from the rest service of the spring transformer application 
	* [link for configuraiton and deplayment and setup ](esp8266-transformer-rest-client/README.md)		

### ARDUINO code
* forwarding data to arduino with servo turnout configuration 
	* [link for configuraiton and deplayment and setup ](arduino-slave-node-servoswitch-ledsignal/README.md)		
* forwarding data to arduino with relay switich snap turnout configuraion 
	* [link for configuraiton and deplayment and setup ](arduino-slave-node-snapswitch-ledsignal/README.md)		 

---

## FOR SENSORS | BLOCK OCCUPANCY SENSORS 

### ESP code 
* configuraing the sensros for block occupancy 
	* direclty publishing data to the MQTT topic 
		* [link for configuraiton and deplayment and setup ](esp8266-sensors-mqtt-client/README.md)		
	* publishing data to the spring transforer application via rest endpoints 
		* [link for configuraiton and deplayment and setup ](esp8266-sensor-rest-client/README.md)		

### ARDUINO code 		
* configuring ir sensor based block decection arduino node 
	* [link for configuraiton and deplayment and setup ]()		
* configuring ct sensor based block decection arduino node 		
	* [link for configuraiton and deplayment and setup ]()		

----

### [MQTT SETUP GUILDE LINK ](MQTT-SETUP-README.md)

### [JMRI MQTT CONNECTION SETUP AND TESTING LIGHT SIGNAL TURNOUT SENSORS ](JMRI-MQTT-SETUP-README.md)

### [CONNECTION DETAILS FOR ESP AND ARDUINO ](ESP-ARDUINO-CONNECTON-README.md)


## SPRING TRANSFORMER APPLICATION 

### [SPRING TRANSFORMATOIN APPLICATION SETUP AND EXECUTION ](spring-jmri-mqtt-data-transformer/README.md)


## FOR SIGNAL LIGHT AND TURNOUT 

### [ESP8266 MQTT SUBSCRIBER CONFIGURATION ](esp8266-transformation-mqtt-client/README.md)		

### [ESP8266 REST CLIENT SUBSCRIBER CONFIGURATION ](esp8266-transformer-rest-client/README.md)	

### [ARDUINO SERVO TURNOUT & SIGNALS NODE CONFIGURATION ](arduino-slave-node-servoswitch-ledsignal/README.md)

### [ARDUINO RELAYSWITCH SNAP TURNOUT & SIGNALS NODE CONFIGURATION ](arduino-slave-node-snapswitch-ledsignal/README.md)	


## FOR SENSORS | BLOCK OCCUPANCY SENSORS 

### [ESP8266 MQTT PUBLISHER CONFIGURATION  ](esp8266-sensors-mqtt-client/README.md)	

### [ESP8266 REST CLIENT PUBLISHER CONFIGURATION ](esp8266-sensor-rest-client/README.md)	

### [ARDUINO IR SENSORS NODE CONFIGURATION  ](arduino-slave-node-ir-sensor-client/README.md)	

### [ARDUINO CT SENSORS NODE CONFIGURATION ](arduino-slave-node-ct-sensor-client/README.md)	
