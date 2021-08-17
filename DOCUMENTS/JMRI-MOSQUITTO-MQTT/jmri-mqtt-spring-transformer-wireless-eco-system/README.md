# JMRI MQTT DATA TRANSFORMER APPLICATION 

> Jmri will push the data to the mqtt \
> spring transformer application configured with nodes and its details like no of turnout, no of signals, no of light in the node \
> transformer application will read the data from mqtt topics which is pushed by jmri and transform that data and transformed  \
> and push back to the mqtt node wise, also store in end points cache if enabled for serving data via rest endpoints  \
> node wise topics for each esp8266 node will have only relevant data\
> this will reduce the processing on the esp8266 so that it can handle node specific data properly. \
> esp8266 will read data from mqtt nodewise topoics or can direclty make http rest endpoint call to spring application and get the data \
> esp8266 will pass the data to the arduino via serial line and arduino will do the rest for signals, turnouts, or lights \

----

### ![MQTT SETUP GUILDE LINK ](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/jmri-mqtt-spring-transformer-wireless-eco-system/MQTT-SETUP-README.md)


### Connection details from esp to the arduino 
```
conect the gnd from arduino to the -ve line of the breadboard 
take nodemcu/esp8266 connect the gnd/-ve from breadboard to the gnd of the nodemcu/esp8266
take the tx pin of the nodemcu/esp8266 and connect to the rx pin of the arduino 
take the rx pin of the nodemcu/esp8266 and connect to the tx pin of the arduino 

```

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/jmri-mqtt-spring-transformer-esp8266-arduinouno/image/con.JPG)