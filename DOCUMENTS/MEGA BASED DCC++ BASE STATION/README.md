
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/DOCUMENTS/MEGA%20BASED%20DCC%2B%2B%20BASE%20STATION/mega%20cmri.png)

### 1 step (download the dcc++ software code for ardiuno)
```
Download the cmri code from the below url repository 
https://github.com/DccPlusPlus/BaseStation
```

### 2 step (configure the dcc++ code in the arduino ide)
```
connect the ardiuno mega oard the system 
extrct the zip file and then go inside the in DCCpp_Uno directory 
open the file "DCCpp_Uno.ino" in the arduino ide 
```

### 3 step ( configure and upload the code to arduino)
```
ensure the port and board type uno is selected in tools 

compile the file by clicking the right button on the top 

if its compile the uno is compable for the dcc++

then upload the code to the mega if the code compile sucessfuly 
```

### 4 step (setting up the arduino for dcc++)
```
now once code is uploaded to mega then 

open the serial monitor and then select the  boradrate to 115200 

we can see some dcc++ serial messages 

```

### 5 step (testing the comptablity of the arduino for dcc++ base station code )
```
now in the serial monitor send some cmd to the dcc++ uno board for seding singla 
Example 
<1> for seding on signal 
<0> for sending off signal 
<D> for deginoes the systems 
```


### 6 step (enable the moter shield for dcc++)
```
take moter shield then cut the botton "vin connect" and test it from multimeter 

put the multimeter to the "wifi signal sign" red in VmA and black in Com 
then once touch the both wire together it will make beep if wire is connected 

now mount the moter shield on the top of mega from starting point  
```

### 7 step (test the moter shield for dcc++ compatablity)
```
put the jumper from pin 13 to pin 4

connect the moter shield to the power adapter using helper socket which will go in the vcc and gnd on the motor shield 
then A- and A+ will go to the operation track 
then B- and B+ will go to the programming track

now connect the uno to the computer and then 

now in the serial monitor send some cmd to the dcc++ mega board for seding sinnal 
send <1> cmd then motor shield all 4 light will turn on 
send <D> cmd then motor shield all 4 light will blinking 

```

### 8 step (install jmri and configure the dcc++ base stattion)
```
install java 8 and jmri on the laptop or raspberri pi 

then open "panel pro" -> preferences -> connections 
click on + button on tab 
System manufacturer : DCC++
System Connection : DCC++ Serial Port 

	Serial Port : cu.usbmodem14201 
	Connection Prefix: D
	connection Name : DCC++
	click on ADdition connection Settings 
		Baud rate : 115200bps 
Click on the Save button and restrat 

```


### 9 step (using jmri inbuilt panal to control the train)
```
place engine on the programming track 

then open "panel pro" -> roster -> click on the Red button on roster 
now we hear the sound of the locomotive 
ensure the "programming tack" radio botton is slected in the botton 
then click on the "new loco" botton 
click the botton "read from the decoder" botton 
provide the long address and name then click on the save button
then place the loco on the main track/operattion track then 
then select the loco on thee roster and then open the throttle to operate the engine 
```


### 10 step (using phone or table to control the train)
```
then open "panel pro" -> preferences -> withrottle
check the "start automatically with application" check box and save and restart 
once restart then check on redbotton to start the application it will turn to green 
in pone /table in withrottle/engine driver app provide the host name and the port number to configure the cmri server then 
use the app to controll the engine on dcc++ layout 

```

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/DOCUMENTS/MEGA%20BASED%20DCC%2B%2B%20BASE%20STATION/IMG_6099.HEIC)
