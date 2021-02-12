# CMRI MULIT COMPONENT NODE SENSORS, SIGNALS. SERVO TURNOUTS

---

## FUNCTIONALITY 

```
# SERVO TURNOUT 
32 servo using PCA9685 address from 1001 to 10032 
 	1st board 1001 to 1016
	2nd board 1017 to 1032

## INFRARED SENSOR BASED BLOCK SENSOR 
5 blocks with IR sensors address from 1001 to 1005 
    10001 for 1st block 
    1002 for 2nd block 
    1003 for 3rd block 
    1004 for 4th block 
    1005 for 5 block 

## SIGNALS BASED ON LED RED GREEN YELLOW 
16 led using PCF8674 address from 1033 to 1048 
	1st board 1033 to 1040
	2nd board 1041 to 1048

```

## Connections details 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-mulit-component-node/Connections.JPG)

```
+5v External power supply to the breadboard 

connect the SDA and SCL line from arduino to the breadboard 
Pullup the SDA and SCL 
	connect one  resistor from +5v to the SCL ine in breadbaord 
	connect one  resistor from GND to the SDA line in breadbaord

Common Ground 
 	connect one jumper from arduino Gnd to the breadboard Gnd of the external power supply for common ground 

--------------------------------------------------------------------------------------------------------------------------------------------

## PCF8674 CONNECTION FOR SIGNAL LIGHTS 
connect the SDA and SCL line from breadboard to the SDA and SCL pin of the PCF8674 1st board
then connect the 2nd PCF8674 bord to the 1st board from behind 
then take the +5v and gnd from breadboad to the vcc and gnd of the PCF8674 1st board.
then take the vcc pin of the 2nd board and connect the seprate signal breadboard positive line 

then connect the p0 to p7 line from the 1st board PCF8674 to the signal breadboard short leg of green yellow red led leg 
then connect the risistor for signal breadboard  +ve to the ristor one leg and other leg of the risistor will join the led long legs 

then connect the p0 to p7 line from the 2nd board PCF8674 to the signal breadboard short leg of green yellow red led leg 
then connect the risistor for signal breadboard  +ve to the ristor one leg and other leg of the risistor will join the led long legs 

## SIGNALS BASED ON LED RED GREEN YELLOW 
16 led using PCF8674 address from 1033 to 1048 
	1st board 1033 to 1040
	2nd board 1041 to 1048

--------------------------------------------------------------------------------------------------------------------------------------------

## PCA9685 CONNECTIONS FOR SERVO TURNOUT 
connect the SDA and SCL line from breadboard to the SDA and SCL pin of the PCA9685 1st board 
then take the +5v and gnd from breadboad to the vcc and gnd of the PCA9685 1st board where sda nad scl pins co-exisist 
then take the +5v and gnd from breadboad to the vcc and gnd of the PCA9685 1st board. left side center power supply 
connect the 6 pins female jumper form 1st board PCA9685 to the 2nd PCA9685 board 
connect the servo to the pin no 0 onwards in board 1 and board 2 

# SERVO TURNOUT 
32 servo using PCA9685 address from 1001 to 10032 
 	1st board 1001 to 1016
	2nd board 1017 to 1032


--------------------------------------------------------------------------------------------------------------------------------------------	

## BLOCK SENSORS WITH INFRA RED 

take seprate breadboard for the seprate block 
here we have3 block max block suppored on uno is 5 after tha pin will not be their for mega we can extends 
then take +5v and gnd from external power supply to the blocks breadboard 

then place 1st LED TO THE blocks boreadboard1
connect the vcc and gnd from the blocks breadboard1
connect the out pin of the IR sensor to the pin 3 of arduino 

then place 2nd LED TO THE blocks boreadboard1
connect the vcc and gnd from the blocks breadboard1
connect the out pin of the IR sensor to the pin 4 of arduino 

-----
connect the +5v and gnd from blocks breadboard1 
then place 1st LED TO THE blocks boreadboard2
connect the vcc and gnd from the blocks breadboard2
connect the out pin of the IR sensor to the pin 5 of arduino 

then place 2nd LED TO THE blocks boreadboard2
connect the vcc and gnd from the blocks breadboard2
connect the out pin of the IR sensor to the pin 6 of arduino 

------
connect the +5v and gnd from blocks breadboard2 
then place 1st LED TO THE blocks boreadboard3
connect the vcc and gnd from the blocks breadboard3
connect the out pin of the IR sensor to the pin 7 of arduino 

then place 2nd LED TO THE blocks boreadboard3
connect the vcc and gnd from the blocks breadboard3
connect the out pin of the IR sensor to the pin 8 of arduino 


## INFRARED SENSOR BASED BLOCK SENSOR 
5 blocks with IR sensors address from 1001 to 1005 
    10001 for 1st block 
    1002 for 2nd block 
    1003 for 3rd block 
    1004 for 4th block 
    1005 for 5 block 

```


## CMRI CONFIGURATION IN PANEL PRO
```
CMRI PanelPro. When it is running click on edit preferences to get the following window

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
panel pro -> prefrences -> connection -> click on addition configration ->  add nodes 

click on add node 
provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: SMINI 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 

```

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-mulit-component-node/all-components.png)

## Configure the Sensor

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-mulit-component-node/SENSORS-COFIG.png)

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

## INFRARED SENSOR BASED BLOCK SENSOR 
5 blocks with IR sensors address from 1001 to 1005 
    10001 for 1st block 
    1002 for 2nd block 
    1003 for 3rd block 
    1004 for 4th block 
    1005 for 5 block 
```


## Configuring the servo

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-mulit-component-node/TURNOUTS-CONFIG.png)

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


# SERVO TURNOUT 
32 servo using PCA9685 address from 1001 to 10032 
 	1st board 1001 to 1016
	2nd board 1017 to 1032
```


## Configartion of the Signal heads leds 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-mulit-component-node/1-SIGNALHEAD.png)

##for barod 1
```

## SIGNALS BASED ON LED RED GREEN YELLOW 
16 led using PCF8674 address from 1033 to 1048 
	1st board 1033 to 1040
	2nd board 1041 to 1048


PANEL PRO -> tools -> sinnals heads -> add 


  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1033 

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1034

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1035 


Note Repeate this for all the signal lights 

  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1038

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1037  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1036      

```

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-mulit-component-node/2-SIGNALHEAD.png)
## FOR BOARD 2
```
PANEL PRO -> tools -> sinnals heads -> add 


  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1043 

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1042  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1041  


Note Repeate this for all the signal lights 

  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1046

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1045  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1044     
```