# Infrared Sensor Jmri Block decection 

---

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-485-infrared-sensor-block-decection/IMG_6256.JPG)

## Connection details 

```
# Arduino Connection 

Run the +5v power bus supply and connect all ir sensor on vcc pin  
Run the -gnd power bus supply and connnect all ir sensor on gnd pin 
Run the pin 3 bus and collect all the ir sensor on out pin
+5v to all the  IR sensor vcc in chain 
gnd to all the IR sensor gnd in chain 
pin 3 to all the IR sensor OUT pin 

connect the led to the pin 13 with gnd 

```

# CMRI CONFIGURATION IN PANEL PRO

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

# configure the nodes so click on "Configure C/MRI nodes"

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

# Configure the Sensor 

```
Open Panel pro 
tools -> table -> sensors ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


   click on sensors window on top menu Defaults -> Initial Sensor state -> provide inactive in open popup window and -> click on "ok" button 

```

# Configure in Layout Editor 

```
Click on Panel Pro window then top menu -> Panel -> New Panel -> Layout Editor 

Click on "Anchor Point" Radio Button then press "Shit key" than do click on the editor we can see the start point is visible on the editor 
do the same for end point of the track 

Click on the "Track Segment" radio button then check "Mainline" and "Dashed" check button then  Block Name select the sensor name which we created earlier 
click on "Highlight" Checkbox and "Block Sensor" Name select from drop down sensor which we have created earlier 
then keep pressing "shift key" and select the point start and drag to the point end track light will apper 

then test the sensor by moving hand on the top of them and in editor track will turn into red 

then save the editor by CRT+ S and provide the name to that and select the location where we want to save the layout information 

```