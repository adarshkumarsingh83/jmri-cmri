

# [mosquitto mqtt](https://mosquitto.org/)


## To install brew 
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

## To install mosquitto
$ brew install mosquitto


## doucmentation 
* [documentation](https://mosquitto.org/man/mosquitto-8.html)


## To Create custom mosquitto.conf
### [for help ](https://mosquitto.org/man/mosquitto-conf-5.html)
* vi mosquitto.conf
* press i for insert then copy paste below content 
```
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous true         #Allows JMRI to subscribe without an ID or password
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 

## Start with Configuration  
* To Run with Default Configuration 
	* $ /usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf
* To Run with Custom Configuration 
	* $ /usr/local/sbin/mosquitto -c ./mosquitto.conf

## To subscribe data on mqtt 
### open a new terminal window 
* mosquitto_sub -h localhost -v -t '/trains/#'

## To publish Data on mqtt 
### open a new terminal window 
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "CLOSED"
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "THROWN" 


## python script for start and stop the mosquitto
### Start script with default configuraiton 
* vi start-mos.py
```
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the scripty 
	* python start-mos.py 

### Start script with custom configuraiton 
* vi start-cust-mos.py
```
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c ./mosquitto.conf',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the scripty 
	* python start-cust-mos.py



### Stop script 
* vi stop-mos.py
```
import subprocess

subprocess.call('killall mosquitto',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the scripty 
	* python stop-mos.py 

# JMRI WITH MQTT MOSQUITTO
* [JMRI DOC LINK ](https://www.jmri.org/help/en/html/hardware/mqtt/index.shtml)

----

## JMRI WILL CREATE FOLOWING CHANNEL IN MQTT
* /trains/track/light/[LIGHT_NO] [STATUS] ON|OFF
* /trains/track/turnout/[TURNOUT_NO] [STATUS] THROW|CLOSE
* /trains/track/sensor/[SENSOR_NO] [STATUS] ACTIVE|INACTIVE

```
$ python start-mos.py

$ mosquitto_sub -h localhost -v -t '/trains/track/#'
/trains/track/light/3 OFF
/trains/track/light/3 ON
/trains/track/turnout/1 THROW
/trains/track/turnout/1 CLOSED
/trains/track/sensor/1 INACTIVE
/trains/track/sensor/1 ACTIVE

$ python stop-mos.py

```



### start the mqtt server and connect the jmri to the mqtt server 
```
* $ python start-mos.py

* panel pro -> preferences -> Connections 

System Manufacturer => MQTT
System connection => MQTT 
Settings 
   hostname : localhost
   connection prefix : M 
   Connection Name : MQTT 
   check on additional connection setings 


 save the connection it will be saved and connected to the mqtt server 


```

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/1.png)

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/2.png)

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/3.png)

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/4.png)

### create a terunout  
```
Panel pro -> tools -> tables -> turnout -> 
click on add button 

 System Connection : MQTT 
 Hardware ADdress : 1 
 User Name : T1 

 Click on Create button 
 NOTE : Light and Turnout will share the same output address slots so don't use same for light and turnout 
 NOTE : do it for the number of turnout we want to create 

```
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/5.png)

### create a Light  
```
Panel pro -> tools -> tables -> Light -> 
click on add button 

 System Connection : MQTT 
 Hardware ADdress : 3 
 User Name : L3 

 Click on Create button 
 NOTE : Light and Turnout will share the same output address slots so don't use same for light and turnout 
 NOTE : do it for the number of Light we want to create 


```

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/6.png)

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/7.png)

### Testing Turnout with MQTT 
```
start the terminal mqtt client to see the output of the jmri cmd executed behind the turnout and light button 

$ mosquitto_sub -h localhost -v -t '/trains/track/#'

and click on the T1 and T2 turnout button throw and close and see the output of them in the console of mqtt client 

```
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/8.png)

### Testing Light with MQTT 
```
start the terminal mqtt client to see the output of the jmri cmd executed behind the turnout and light button 

$ mosquitto_sub -h localhost -v -t '/trains/track/#'

and click on the L3 and L4 light button on and off and see the output of them in the console of mqtt client 

```
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/9.png)



