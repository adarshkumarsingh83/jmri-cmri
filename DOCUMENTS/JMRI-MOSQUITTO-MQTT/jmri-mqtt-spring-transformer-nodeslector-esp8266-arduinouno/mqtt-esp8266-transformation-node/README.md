# MQTT ESP8266 

---

> esp will conect to mqtt via wifi network 
> wifi credentials will be configured in Config.h file 
```
const char* ssid = "adarsh_radha_2G"; // ESP8266 do not support 5G wifi connection
const char* wifi_password = "*******";
```
> mqtt configuration and credentail will be configured in Config.h file 
```
const char* mqtt_server = "192.168.0.188"; 
const char* mqtt_username = "adarsh";
const char* mqtt_password = "password";
```
> mqtt topics will be configured in Config.h 
```
// change the node "number/name"  based on the node default is 1 in this 
const char* mqtt_topic = "/amt/node/1/#";
const char* mqtt_topic_light = "/amt/node/1/light/";
const char* mqtt_topic_turnout = "/amt/node/1/turnout/";
const char* mqtt_topic_signalhead = "/amt/node/1/signal/";
```

> esp client id is configure in Config.h 
```
const char* clientID = "JMRI_SUBSCRIBER_NODE_ESP8266_1";

```


### Connection details 

```
conect the gnd from arduino to the -ve line of the breadboard 
take nodemcu/esp8266 connect the gnd/-ve from breadboard to the gnd of the nodemcu/esp8266
take the tx pin of the nodemcu/esp8266 and connect to the rx pin of the arduino 
take the rx pin of the nodemcu/esp8266 and connect to the tx pin of the arduino 

```


![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/jmri-mqtt-spring-transformer-esp8266-arduinouno/image/con.JPG)