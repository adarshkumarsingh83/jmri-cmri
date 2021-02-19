

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-485-single-node-led/connections-details.png)

### CMRI library

- https://github.com/madleech/ArduinoCMRI

### RS485 library

- https://github.com/madleech/Auto485

---


### CMRI CONFIGURATION IN PANEL PRO

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

### NODE CONFIGUATION IN JMRI

```
CMRI PanelPro. ->  preferences ->  connections to get the following window

click on add node 

provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: SMINI 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 
```


### Light configuration on jmri 
```
Put 1 in the node address and then click add node button. then click done. save configuration and restart JMRI
setup the lights control in the JMRI table. Click on tools > table > lights


System connection: name you gave your arduino
Hardware address: 1001
User name: (enter what you want to call this light, I used lightTest for this)
click create new then cancel, you will get a warning reminding you to save this table
You should now have the following in your lights table

click on the  light on/off button
```



