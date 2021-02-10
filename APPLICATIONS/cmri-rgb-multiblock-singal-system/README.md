# RGB Multblock decection system 

--- 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-rgb-multiblock-singal-system/CONNECTIONS-0.JPG)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-rgb-multiblock-singal-system/CONNECTIONS-1.JPG)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-rgb-multiblock-singal-system/CONNECTIONS-2.JPG)

## Connection Deatils 

```
  
Assumption: 
Train can travel from both direction of the block 
every block start will have IR sensor and end will also have IR sensor 
train has to click both 1st and 2nd IR sensor one by one either of the direction 
otherwise it will not show as UnOccupoied even train left the block 

1.connection the +5v and gnd to the breadboard 
2.connection led1 and led2 to the breadboard gnd long leg (common cathod rgb led) 
3. then connection 2 resistor to the red and green led of the rgb led for both led1 and led2 
4. then connect the green long leg of led1 to the 3 pin in arduino  
5. then connection the red long  leg led11 to the 4 pin in arduino  
6. then connect the green long leg of led2 to the 5 pin in arduino  
7. then connect the red long  leg led2 to the 6 pin in arduino  
8. then connect the IR sensor 1 and 2 to the bread board 
9. then connect the vcc and gnd to the IR sensor from breadboard +5 and gnd 
10 then connect the IR sensor1 out to the A0 pin in arduino 
11 then connect the IR sensor2 out to the A1 pin in arduino 
12. then connect pin 6 on arduino to the breadboard column which will go the the previous and next block for occupied signal 
13. take one connection to the previous block arduino and connect to the A3 pin of that 
14. take one connection to the next block arduion and connect to the A2 pin of that 
15. take previous block incomming occupied singal connection to the pin A2 of the arduino 
16. take next block incomming occupied sinal cconnection to the pin A3 of the arduino 
17. take the connection from gnd pin from arudino to the next and previous block gnd 
	pins connect all gnd to tmake common ground bus for entre block system. 

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

### configure the nodes so click on "Configure C/MRI nodes"
```
click on add node 
provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1
 #define CMRI_ADDR 2
 #define CMRI_ADDR 3

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


#NOTE we have to do it for 3 time for 3 blocks 

## for Nodes address in Jmri 

## for Node 1 address is 1000
sensor address will be 1001

## for Node 2 address is 2000
sensor address will be 2001

## for Node 3 address is 3000
sensor address will be 3001

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

```
