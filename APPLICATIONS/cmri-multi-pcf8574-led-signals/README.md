# JMRI CMRI MULTI PCF8574 SIGNAL

---

## Connection details
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pcf8574-led-signals/connectionsdetails.JPG)
```
arduino scl and sda to the pcf8574 pins to sda and scl 
then use seprate 5v+ supply to power up the pcf8574 to the first board vcc and gnd gnd will go to the arduino gnd also 
arduino pin 3 to the intrupt pin which is INT ON pcf8574
pcf8574  p0 to p7 pins to the breadboard short leg of the led  
connect the +5v power supply for all the 1k resistor and then other end of resisot will go to the long leg of leds 
pcf8574 other end whill have chained pcf8574 board 

 board 1... 8 
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

### jumper configuartion for the addition boards 
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pcf8574-led-signals/pca8574%20addressing%20configuration.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pcf8574-led-signals/pcf.png)
```
# Addressing configuation via jumper 

	A2 A1 A0      address of board 
----------------------------	
	0  0   0   =  0x20
	0  0   0   =  0x21
    0  1   0   =  0x22
    0  1   1   =  0x23
    1  0   0   =  0x24
    1  0   1   =  0x25
    1  1   0   =  0x26
    1  1   1   =  0x27
```

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

### FOR BOARD 1 
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pcf8574-led-signals/1%20board%20config.png)
```
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

NOTE 1007 AND 1008 CAN BE USED FOR OTHER PURPOSE OR MIXED WITH 1015 AND 1016 
 ```

### FOR BOARD 3 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pcf8574-led-signals/2%20board%20config.png)
```
PANEL PRO -> tools -> sinnals heads -> add 


  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1011 

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1010  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1009  


Note Repeate this for all the signal lights 

  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1014

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1013  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1012     


NOTE 1015 AND 1016 CAN BE USED FOR OTHER PURPOSE OR MIXED WITH 1006 ADN 1007 

 ```

