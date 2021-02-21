# BLOCK DECETION BY USING IR SENSOR AND PCF8574 COMMON ANNON LED 

---

![img](https://github.com/adarshkumarsingh83/arduino/blob/master/APPLICATION/pcf8574-irsensor-block-signal/image/common-annod-led.png)

![img](https://github.com/adarshkumarsingh83/arduino/blob/master/APPLICATION/pcf8574-irsensor-block-signal/image/led-connection.png)


![img](https://github.com/adarshkumarsingh83/arduino/blob/master/APPLICATION/pcf8574-irsensor-block-signal/image/multi-node-connection.JPG)

![img](https://github.com/adarshkumarsingh83/arduino/blob/master/APPLICATION/pcf8574-irsensor-block-signal/image/connection.JPG)



### Connections

```
connect sda and scl from arduino to the pcf8574 sda and scl pin 
take +5v and gnd from arduino to the breadboard and then from their to pcf8574 vcc and gnd pin 
from pcf8574 board pin p0 to p5 connect to the breadboard 6 resistors 
connect the 2 connom annod leds to the resistos short led 
log leg of the led will connect to the positive +ve of the breadboard 
take pcf8574 other end vcc and connect to the breadboard +ve 
take the +ve and gnd from breadboard and add to the two IR sensor on the breadboard 
then connect the out pin of sensor1 to the A0 and out pin of the sensor2 to the A1 pin of the arduino 

take the pin 7 from arduino to the breadboard then send to the previous and next block arduino for block occupied singal transmission 
from the previous block occupied singal transmission will connect to the pin A2 
from the next block occupied singal transmission will connect to the pin A3 

# led pin sequence with pcf8574 is important to get the propeer sinal ligtts 
       p0 red1
       p1 green1
       p2 yellow1
       p0 red2
       p1 green2
       p2 yellow2
 ```