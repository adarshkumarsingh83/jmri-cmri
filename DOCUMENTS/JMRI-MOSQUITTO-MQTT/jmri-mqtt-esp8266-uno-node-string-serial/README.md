# JMRI MQTT SUBSCRIBER ESP8266/NODEMCU ARDUINO SERIAL STRING COMMUNICATION 

----

### jmri configuration 
* all sensors will start from 1 to limit 
* all the light are started with 1000 onwards to 1999 address on jmri
* all the turnout are started with 2000 onwards to 2999 address on jmri
* all the signal are started with 3000 onwards address on jmri


### Connection details 

```
conect the gnd from arduino to the -ve line of the breadboard 
take nodemcu/esp8266 connect the gnd/-ve from breadboard to the gnd of the nodemcu/esp8266
take the tx pin of the nodemcu/esp8266 and connect to the rx pin of the arduino 
take the rx pin of the nodemcu/esp8266 and connect to the tx pin of the arduino 

```
