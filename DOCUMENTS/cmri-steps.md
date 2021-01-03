
### 1 step
```
Download the cmri code from the below url repository 
https://github.com/DccPlusPlus/BaseStation
```

### 2 step
```
extrct the zip file and then go inside the in DCCpp_Uno directory 

open the file "DCCpp_Uno.ino" in the arduino ide 
```

### 3 step
```
ensure the port and board type uno is selected in tools 

compile the file by clicking the right button on the top 

if its compile the uno is compable for the dcc++

then upload the code to the uno if the code compile sucessfuly 
```

### 4 step
```
now once code is uploaded to uno then 

open the serial monitor and then select the  boradrate to 115200 

we can see some dcc++ serial messages 

```

### 5 step
```
now in the serial monitor send some cmd to the dcc++ uno board for seding singla 
Example 
<1> for seding on signal 
<0> for sending off signal 
<D> for deginoes the systems 

example 1
add jumper cable to pin 13 to pin 3 and led to go off 
send cmd <1> to led on and <0> for off 

example 2
add jumper cable to pin 13 to pin 11 and led to go off 
send cmd <1> to led on and <0> for off 


example 3
add jumper cable to pin 13 to pin 5 
send cmd <D> to led will blink in faster rate 

example 4
add jumper cable to pin 13 to pin 10 
send cmd <D> to led will blink in slower rate 
```


### 6 step
```
take moter shield then cut the botton "vin connect" and test it from multimeter 

put the multimeter to the "wifi signal sign" red in VmA and black in Com 
then once touch the both wire together it will make beep if wire is connected 

now mount the moter shield on the top of uno 
```

### 7 step
```
put the jumper from pin 12 to pin 10 
put the jumper from pin 13 to pin 5

connect the moter shield to the power adapter using helper socket which will go in the vcc and gnd on the motor shield 
then A- and A+ will go to the operation track 
then B- and B+ will go to the programming track

now connect the uno to the computer and then 

now in the serial monitor send some cmd to the dcc++ uno board for seding sinnal 
send <1> cmd then motor shield all 4 light will turn on 
send <D> cmd then motor shield all 4 light will blinking 

```

### 8 step
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


### 9 step
```
place engine on the programming track 

then open "panel pro" -> roster -> click on the Red button on roster 
now we hear the sound of the locomotive 
ensure the programming tack radio botton is slected in the botton 
then click on the new loco botton 
click the botton "read from the decoder" botton 
provide the long address and name then save it 
then select the loco on thee roster and then open the throttle to operate the engine 
```


### 10 step
```
then open "panel pro" -> preferences -> withrottle
check the "start automatically with application" check box and save and restart 
once restart then check on redbotton to start the application it will turn to green 
in pone /table in withrottle/engine driver app provide the host name and the port number to configure the cmri server then 
use the app to controll the engine on dcc++ layout 

```
