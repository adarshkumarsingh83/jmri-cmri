

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-485-multiple-node-leds/connections-details.png)

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



click on confiugure nodes to bring up the nodes page
In the node address put 1 in for the first Arduino and click Add Node, then click on configure nodes again so we can add the second Arduino which will be node 2. Each Arduino you add in this way will need a seperate node addresss. Once this has all been done make sure you save the settings and restart PanelPro so that all the settings are implemented.

Once PanelPro has restarted click on tools > tables > lights so we can add a light control for each Arduino.
first Arduino the address will be 1001 and 
for the second Arduino the address will be 2001 and 
for the third Arduino the address will be 3001 and 
for the forth Arduino the address will be 4001 and 
for the fifth Arduino the address will be 5001 and 
for the sixth Arduino the address will be 6001 
and so on 


Once you have added both these addresses to your table you are done. Click on the light buttons for each address and the on board LED on the corresponding Arduino should come on/off. You now have two Arduino's with 48 outputs and 24 inputs each.
```



### CMRI library

- https://github.com/madleech/ArduinoCMRI

### RS485 library

- https://github.com/madleech/Auto485