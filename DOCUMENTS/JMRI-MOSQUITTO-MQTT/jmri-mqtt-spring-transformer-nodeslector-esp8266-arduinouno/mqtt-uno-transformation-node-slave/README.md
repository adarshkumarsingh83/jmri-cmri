# Arduino Uno/mega client for processing 

---

> arduino client will connect to the esp via seraila Rx/Tx pins 
> gnd will be common in both the devices 


### Configuration of the starting address of the light turnout and signals 
```
#define LIGHT_START_ADDRESS 1000
#define TURNOUT_START_ADDRESS 2000
#define SIGNAL_START_ADDRESS 3000
```


### Connection details 
```
conect the gnd from arduino to the -ve line of the breadboard 
take nodemcu/esp8266 connect the gnd/-ve from breadboard to the gnd of the nodemcu/esp8266
take the tx pin of the nodemcu/esp8266 and connect to the rx pin of the arduino 
take the rx pin of the nodemcu/esp8266 and connect to the tx pin of the arduino 

```


![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/jmri-mqtt-spring-transformer-esp8266-arduinouno/image/con.JPG)