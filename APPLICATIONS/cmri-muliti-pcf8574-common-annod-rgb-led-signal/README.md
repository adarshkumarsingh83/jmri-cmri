# PCF8574 COMMON ANNON LED SIGINAL HEAD 

---

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/pcf.png)

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/pca8574-addressing-configuration.png)

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/common-annod-led.png)

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/connections.JPG)

### Connections

```
# follow the below same steps for all the block nodes in the system 

connect sda and scl from arduino to the pcf8574 sda and scl pin 
take +5v and gnd from arduino to the pcf8574 vcc and gnd pin 

board1 
from pcf8574 board1 pin p0 to p5 connect to the breadboard1 6 resistors for common annod leds 
connect the 2 connom annod leds from short leg side to the resistos which was added earlier 
then one long leg of the led will connect to the positive +ve of the breadboard 
connect the pcf8574 barod2 

board2 
adjust the address of the board by setting up the jumper 
from pcf8574 board2 pin p0 to p5 connect to the breadboard1 6 resistors for common annod leds 
connect the 2 connom annod leds from short leg side to the resistos which was added earlier 
then one long leg of the led will connect to the positive +ve of the breadboard 
connect the pcf8574 barod3 

board3 
adjust the address of the board by setting up the jumper 
from pcf8574 board2 pin p0 to p5 connect to the breadboard1 6 resistors for common annod leds 
connect the 2 connom annod leds from short leg side to the resistos which was added earlier 
then one long leg of the led will connect to the positive +ve of the breadboard 
connect the pcf8574 barod..N


take last pcf8574 other end vcc and connect to the breadboard +ve which long leg of leds are connected 
and pass it to the all the boards breadboard +ve for common annod led long leg 

# led pin sequence with pcf8574 is important to get the propeer sinal ligtts 
       p0 red1
       p1 green1
       p2 yellow1
       p0 red2
       p1 green2
       p2 yellow2
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

## Node configuation 
```
Panelpro -> Preferences -> Connection -> click on add node 

provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: SMINI 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 
```


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/signalhead.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/1SH.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/2SH.png)

## Signal head configuations board1
 ```
NOTE WE CAN KEEP ONE RESERVE JMRI ADDRESS AND USE IT FOR ALL THE YELLOW ENTRY TO SAVE JMRI ADDRESS 

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
 ```


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/3SH.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/4SH.png)


## Signal head configuations board2
```
NOTE WE CAN KEEP ONE RESERVE JMRI ADDRESS AND USE IT FOR ALL THE YELLOW ENTRY TO SAVE JMRI ADDRESS 

PANEL PRO -> tools -> sinnals heads -> add 

  Drop down select -> Triple Output RGB-> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1010 

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1011 

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
          in our case its 1013

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1014  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1012         

```

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/5SH.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-muliti-pcf8574-common-annod-rgb-led-signal/image/6SH.png)


### ## Signal head configuations board3
```
NOTE WE CAN KEEP ONE RESERVE JMRI ADDRESS AND USE IT FOR ALL THE YELLOW ENTRY TO SAVE JMRI ADDRESS 

PANEL PRO -> tools -> sinnals heads -> add 

  Drop down select -> Triple Output RGB-> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1020

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1021  

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1019  


Note Repeate this for all the signal lights 

  Drop down select -> Triple Output -> 
  Systenm Name : SH_XXX
  User Name : XXXX

  Green Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for green light or pin where green light is connected "
          in our case its 1024

  Yellow Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for yellow light or pin where yellow light is connected "
          in our case its 1023

  Red Output 
    Click on "Create New" radio button 
          "provide address which is mentioned in the arduino code for red light or pin where red light is connected "
          in our case its 1022        
```