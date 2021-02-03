# JMRI-CMRI MULTI COMPONENTS 

--- 


![img]()

---
## Connection details
```
scl and sda to the pca9685 pins to sda and scl 
5v+ and gnd to the pca9685 pins to vcc and gnd
5v+ and gnd to the pca9685 power points from 5v power external supply 
5v+ and gnd to the ir sensor gnd and vcc pins 
arduino pin 3 to the out pin of the ir sensor 
arduino pin 13 to the red led with gnd 

dasy chain the pca9685 and connect the servo on the "0"th point of the pca9685
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
