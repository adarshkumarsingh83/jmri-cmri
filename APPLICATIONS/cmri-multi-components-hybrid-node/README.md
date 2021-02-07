# JMRI-CMRI MULTI COMPONENTS 

--- 


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-components-hybrid-node/CONNECTION-DETAILS.png)

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-components-hybrid-node/CONNECTIONS.JPG)

---
## Connection details
```
+5v and gnd to the breadboard 
scl and sda to the breadboard then connect the one risistor to the sda and another one to the  scl from +5v 
then connect the +5v and gnd from breadboard to the pcf8574 and pca9685 vcc and gnd pins 
then sda and scl from the breadboard to the pcf8574 and pca9685 scl and sda pins 
then +5v and gnd to the pca9685 power input to the gnd and vcc from breadboard
then +5v and gnd to the pcf8574 vcc and gnd pins from the breadboard
connect the gnd from bradboard to the arduino gnd as the common ground 
then from pcf8574 1st and 2nd board p0 to p7 pin to the short leg of the led 
then from bradboard +5v pwersupply to the 220Oms resistors and another leg of the resistor to the long leg of the ledg. 
then connect the servo to the pca9685 boards 

addressing for servo will start from 0 - 31 in uno but in jmri it will start form 1001 to 1032 
addressing for light/signals will start from 1033 to 1048 


```

## CMRI CONFIGURATION IN PANEL PRO

```
MRI PanelPro. When it is running click on edit preferences to get the following window

set the following tabs

System manufacturer = C/MRI

System connection = Serial

Setting

Serial port: (select the port your arduino is connected to, you will find this on the arduino IDE)

Connection Prefix: C

Connection Name: (what ever you want to call it)

Also click on additional connection box and select the Baud rate to 9600 bps

```


## configure the nodes so click on "Configure C/MRI nodes"

```
click on add node 
provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: SMINI 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 

```


## Configure the Sensor
```
Open Panel pro 
tools -> table -> sensors ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


   click on sensors window on top menu Defaults -> Initial Sensor state -> provide inactive in open popup window and -> click on "ok" button 


NOTE : In Arduino code address for the sensor will start from 0 but in jmri it will start from 1 
Example: 
cmri.set_bit(0, xxx);
1st param is sensor address and 2nd is the value we cant to send to jmri 
but while configuringg the sensor will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

```

## Configuring the servo 
```
JMRI 
Tools -> tables -> turnout -> add 

## BOARD NO 1 WITH ADDRESS 40 
-------------------------------
board no 1 with address 40  servo position 0 will be => 1001  use 1 bit study state 
board no 1 with address 40  servo position 1 will be => 1002  use 1 bit study state
.
.
.
..... continue ......
board no 1 with address 40  servo position 16 will be => 1016  use 1 bit study state



## BOARD NO 2 WITH ADDRESS 41
-------------------------------
board no 2 with address 41 servo position  0 will be => 1017    use 1 bit study state 
board no 2 with address 41 servo position  1 will be => 1018    use 1 bit study state 
.
.
.
..... continue ......
board no 2 with address 41 servo position  16 will be => 1032    use 1 bit study state 



## BOARD NO 3 WITH ADDRESS 42
-------------------------------
board no 3  with address 42 servo position 0 will be => 1033    use 1 bit study state 
board no 3 with asddress 42 servo position 1 will be => 1034    use 1 bit study state 
.
.
.
..... continue ......
board no 3 with asddress 42 servo position 16 will be => 1048    use 1 bit study state 



## BOARD NO 4 WITH ADDRESS 43
-------------------------------
board no 4 with address 43 servo poition 0 will be => 1049   use 1 bit study state 
board no 4 with address 43 servo poition 1 will be => 1050   use 1 bit study state 
.
.
.
..... continue ......
board no 4 with address 43 servo poition 16 will be => 1064   use 1 bit study state 


and so on till the number of board mutliplied by 16 total we can have numbers 
```
