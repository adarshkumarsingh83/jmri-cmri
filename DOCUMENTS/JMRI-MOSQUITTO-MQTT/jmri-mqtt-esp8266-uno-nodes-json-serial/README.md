# jmri mqtt subscriber esp8266 master arduino uno slave serial JSON communication 

---

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

### Connection details 

````
gnd from esp8266 to the gnd of the arduino uno 
tx pin of the esp8266 to the rx pin of the arduino uno 
rx pin of the esp8266 to the tx pin of the arduino uno 

````