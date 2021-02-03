# JMRI CMRI MULTI PCF8574 SIGNAL

---


## Connection details 
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