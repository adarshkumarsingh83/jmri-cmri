# JMRI MQTT SUBSCRIBER ESP8266/NODEMCU ARDUINO SERIAL COMMUNICATION 

----

## Lib installtion 

### search for "PubSubClient" lib and install it before compiling 
### or install this lib for location [PubSubClient lib ](https://github.com/adarshkumarsingh83/jmri-cmri/raw/main/DOCUMENTS/JMRI-MOSQUITTO-MQTT/lib/pubsubclient.zip)

----

### Connection details 
```
conect the gnd from arduino to the -ve line of the breadboard 
take nodemcu/esp8266 connect the gnd/-ve from breadboard to the gnd of the nodemcu/esp8266
take the tx pin of the nodemcu/esp8266 and connect to the rx pin of the arduino 
take the rx pin of the nodemcu/esp8266 and connect to the tx pin of the arduino 

```


### cmd to open two seprate aruino ide 
* $ open -n -a Arduino

### cmd to open two aruino serianl monitor for logs 
```
$ screen /dev/cu.usbserial-1410 115200
$ screen /dev/cu.usbserial-1420 115200
```

```
gnd pin from uno to the gnd pin of the esp8266 
D1 pin from esp8266 to the SCL pin of the uno 
D2 pin from esp8266 to the SDA pin of the uno 

```
