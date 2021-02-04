# JMRI CMRI SINGLE PCF8574 SIGNAL

---


## Connection details 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pcf8574-led-signals/connection%20with%20aruiono%20internal%20power.JPG)

* with arudion internal +5v power supply 
```
arduino scl and sda to the pcf8574 pins to sda and scl 
arduino 5v+ and gnd to the pcf8574 pins to vcc and gnd
arduino pin 3 to the intrupt pin which is INT ON pcf8574
pcf8574 other end vcc will go to breadboard positive to power the led 
 connect the 1K resistor one side to the poewr and other side to the long lef of the led 
pcf8574  p0 to p7 pins to the breadboard short leg of the led  
      
      signal first set 
        p0 is for red 
        p1 is for yellow 
        p2 is for green

      signal 2nd set 
        p3 is for red 
        p4 is for yellow 
        p5 is for green 

       then remaning 
         p6  is left  
         p7  is left  



```

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pcf8574-led-signals/connection%20with%20external%20power%20supply.JPG)
* with external +5v power supply 
```
arduino scl and sda to the pcf8574 pins to sda and scl 
external 5v+ and gnd to the pcf8574 pins to vcc and gnd via breadboard 
arduino pin 3 to the intrupt pin which is INT ON pcf8574
all p0 to p7 pin of pcf8574 will go to led short leg 
long leg of led will conected to 220oms resistor and other leg of risistor will be connected to +5v external positive to complete the circuit 
      signal first set 
        p0 is for red 
        p1 is for yellow 
        p2 is for green

      signal 2nd set 
        p3 is for red 
        p4 is for yellow 
        p5 is for green 

       then remaning 
         p6  is left  

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


## JMRI PROCESS FOR SIGNAL HEAD FOR THE SIGNAL LIGHTS 
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pcf8574-led-signals/SIGNALS%20HEAD%20CONFIGURATIONS.png)
````
PANEL PRO -> tools -> sinnals heads -> add 

  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1003 

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1002  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1001  


Note Repeate this for all the signal lights 

  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1006

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1005  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1004 

````

## As light configuration 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pcf8574-led-signals/%20LIGHT%20CONFIGURATIONS.png)
```
 panel pro -> tools -> tables -> light -> add 

 address 1001 
 name xxx 

 click on add button 

  address 1002
 name xxx 

 click on add button 

 address 1003
 name xxx 

 click on add button 
 do it for all the address configured in arduino sktech 
```