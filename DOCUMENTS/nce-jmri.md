# jmri 
https://www.youtube.com/watch?v=XBsbz_ThfSo

https://www.youtube.com/watch?v=TQogIIad-rk

https://www.youtube.com/watch?v=UXzd3K9HfLI


## 1 step 
```
connect the nce power pro to the laptop 
use serial port to usb adapter 
```

## 2. step
``` 
search for "system informaiton" in search finder 
Look in the Hardware -> USB section, expand all and see what devices are present under USB 3.1 
click on the usbtoSerial adapter under the usb it will show the details below 
 Example :-> FT232R USB UART:
 ----------------------------------------------------
 FT232R USB UART:

  Product ID:	0x6001
  Vendor ID:	0x0403  (Future Technology Devices International Limited)
  Version:	6.00
  Serial Number:	A1078WLA
  Speed:	Up to 12 Mb/s
  Manufacturer:	FTDI
  Location ID:	0x14300000 / 5
  Current Available (mA):	500
  Current Required (mA):	90
  Extra Operating Current (mA):	0
--------------------------------------------------------

for trouble shooring remove the usb then refresh the system inforamtion then again plugin and see it will appera in usb 
go to "system informaiton"-> file-> Refresh Information 
```

## 3. step
```
download and install the jmri from below url  
https://www.jmri.org/download/index.shtml
this will install pandelpro , decoderpro soundpro and others 
```

## 4. step 
```
open panelpro or decoderpro -> proferences -> Connections 
provide information of the NCE controller 
----------------------------------------------------------
System Manufacturer : NCE 
Systemn Connection : Serial 
Settings 
	Serial Port : cu.usbserial-A1078WLA 
	Connection Prefix: N
	Connection Name: NCE 
----------------------------------------------------------
Click on save button 
```

## 5. open DecoderPro
```
   it will ask for select active profile 
NOTE: we can see NCE option in the DecoderPro window 
Place the locomotive on the Programming track 
click on the "+ New Loco" button on Decoderpro 
-------------------------------
"Create New Loco " window will appear 
Programming Mode : Direct 
Click on the "Read type from decoder" and check "All" option 

After some time it will read the CV from the locomotivve and show 
Create Basic Roster Entry window in same window 
Provie information 

RosterId: loconumber_type_sequence 
Check on the long option 
provide the active address: and click on "Write" button on botton 
then click on "Save" button Entry will be displayed on roter window 
close that window of new loco entry 
```

## 6. place the newly configure locomotive to the main track 
```
select the loco in the DecodePro entry list then click on throttle button on the botton 
then test run the locomotive from throttle 
```

## 7.go to the DecoderPro -> Action -> Start WiThrottle Servver 
```
   this will pop's up the withrottle server windlow with ip address and port number 
   go to app store in iphone then install the withrottle light into the iphone 
   then open the Withrottle app it will connect to the "my jmri railroad" by default 
   and iphone name will be listed in the withrottle server window onces it connect to the server 
```

## 8. go to the Withrottle app -> Address -> Roster -> 
```
   it will displayed the configured locomotive list 
   select one and click on "Set" botton on the app 
   then got to the Throttle tab from the botton 
   and test run the locomotive which is select from the list earlier 
```


## NOTE: 
```
We can do change of the CV values from DecoderPro 
select the locomotive and double click on that it will open the edit configuration window by which we can do changes and wite back to the decoder 
```







