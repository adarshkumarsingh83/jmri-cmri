# CMRI JMRI SINGLE PCF8574 RGB LED SIGNALS 

---

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pcf8574-rgb-led-signals/connection.JPG)
## Connection details
```
arduino scl and sda to the pcf8574 pins to sda and scl 
arduino 5v+ and gnd to the pcf8574 pins to vcc and gnd
arduino pin 3 to the intrupt pin which is INT ON pcf8574
pcf8574 other end gnd will go to breadboard negative to power the rgb led 
pcf8574  p0 to p7 pins to the breadboard short leg of the rgb led  

Note we are using common cathod rgb led to we are using gnd from pcf8574 to long leg of the rbg led 


signal first set 
        p0 is for red        = cmri address will be 1001
        p1 is for green red  = cmri address will be 1002
        
      signal 2nd set 
        p3 is for red    = cmri address will be 1004
        p4 is for green  = cmri address will be 1005
     
       signal 3nd set 
        p6 is for red    = cmri address will be 1007
        p7 is for green  = cmri address will be 1008
```


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pcf8574-rgb-led-signals/rgb-led-pin.png)

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pcf8574-rgb-led-signals/rgb-specturm.png)

## CMRI CONFIGURATION IN PANEL PRO
```
JMRI PanelPro. When it is running click on edit preferences to get the following window

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
[img]()
```
PANEL PRO -> tools -> sinnals heads -> add 

  Drop down select -> Triple Output RGB-> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1002 

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1003  

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
          in our case its 1005

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1006  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1004 


 Note Repeate this for all the signal lights 

  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1008

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1009  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1007          

```
