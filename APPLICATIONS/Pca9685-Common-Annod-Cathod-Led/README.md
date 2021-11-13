# Pca9685 Common Annod Cathod Led Testing Sample 

----

![img](image/common-annod-cathod-led.png)



## connection details 

* connect sda and scl from arduino to pca9685 sda and scl 
* connect the +5v and -5v from arduino to the pac9685 vcc and gnd 

### for common anode 
![img](image/connection-common-anode.JPG)
* take the pin 0...n yellow pin from pca9685 board and connect to the short legs of common anode led 
* take the vcc from the other end of the pca9685 and connect to the long leg of the common anode led 

### for common cathod 
![img](image/connection-common-cathode.JPG)
* take the pin 0...n yellow pin from pca9685 board and connect to the long legs of common cathod led 
* take the gnd from the other end of the pca9685 and connect to the long leg of the common anode led 


### Configuration in Config.h 
```
#define NO_OF_BOARDS 1


#define BROAD_RATE 9600

## For anode true and for cathod false 
const bool enableAnode = true;

```