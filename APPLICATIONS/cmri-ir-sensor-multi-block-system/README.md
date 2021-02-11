# CMRI IR0SENSORS BLOCK DETECTION 

----

### Connection details
```
+5v and gnd from arduino to the breadboard of block 1 
then supply the smae from breadboard of block 2 and block 3 
pin 3 to the out pin of Sensor start of the block1
pin 4 to the out pin of Sensor end of the block1

pin 5 to the out pin of Sensor start of the block2
pin 6 to the out pin of Sensor end of the block2

pin 7 to the out pin of Sensor start of the block3
pin 8 to the out pin of Sensor end of the block3

connect the jumper from +5v to the vcc of the all the IR sensors of block 1 block 2 and block 3 
connect the jumper from gnd to the gnd of the all the IR sensors of block 1 block 2 and block 3 

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


## Configure the nodes so click on "Configure C/MRI nodes"
```
Panel pro -> preferences -> Connections-> configure nodes 

click on add node 
provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: SMINI 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 
```

## Configure the Sensor
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

NOTE: sensor address from 1001 to 1003 is already their if we want to extends that add more pins and address 

```

## Configure in Layout Editor
```
Click on Panel Pro window then top menu -> Panel -> New Panel -> Layout Editor 

Click on "Anchor Point" Radio Button then press "Shit key" than do click on the editor we can see the start point is visible on the editor 
do the same for end point of the track 

Click on the "Track Segment" radio button then check "Mainline" and "Dashed" check button then  Block Name select the sensor name which we created earlier 
click on "Highlight" Checkbox and "Block Sensor" Name select from drop down sensor which we have created earlier 
then keep pressing "shift key" and select the point start and drag to the point end track light will apper 

then test the sensor by moving hand on the top of them and in editor track will turn into red 

then save the editor by CRT+ S and provide the name to that and select the location where we want to save the layout information 

NOTE do the abo ve action for all the blocks in the arduino 
```