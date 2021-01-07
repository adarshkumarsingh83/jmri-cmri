

[img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-node-led/connections-details.png)

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

### configure the nodes so click on "Configure C/MRI nodes" 
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



