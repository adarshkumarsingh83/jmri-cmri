# JMRI MQTT PUBLISHING SENSOR INFO TO JMRI 

---

## Lib installtion 

### search for "PubSubClient" lib and install it before compiling 
### or install this lib for location [PubSubClient lib ](https://github.com/adarshkumarsingh83/jmri-cmri/raw/main/DOCUMENTS/JMRI-MOSQUITTO-MQTT/lib/pubsubclient.zip)

----

### jmri configuration 
* all sensors will start from 1 to limit 
* all the light are started with 1000 onwards to 1999 address on jmri
* all the turnout are started with 2000 onwards to 2999 address on jmri
* all the signal are started with 3000 onwards address on jmri

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