

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
* w+q  // to save and exit the file 

## start with configration  
$ /usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf


## To subscribe data on mqtt 
### open a new terminal window 
* mosquitto_sub -h test.mosquitto.org -v -t '/trains/#'

## To publish Data on mqtt 
### open a new terminal window 
* mosquitto_pub -h test.mosquitto.org -t /trains/track/turnout/123 -r -m "CLOSED"
* mosquitto_pub -h test.mosquitto.org -t /trains/track/turnout/123 -r -m "THROWN" 


## python script for start and stop the mosquitto
### Start script 
* vi start-mos.py
```
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the scripty 
	* python start-mos.py 

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




```
$ python start-mos.py

$ mosquitto_sub -h localhost -v -t '/trains/track/#'
/trains/track/light/1 OFF
/trains/track/light/ML1 OFF
/trains/track/light/MQTTL1 ON
/trains/track/light/3 OFF
/trains/track/light/4 OFF
/trains/track/turnout/MTT1 CLOSED
/trains/track/turnout/2 CLOSED
/trains/track/turnout/1 CLOSED
/trains/track/sensor/MQTTL1 INACTIVE

$ python stop-mos.py

```


![1](images/1.jpg)
![2](images/2.jpg)
![3](images/3.jpg)
![4](images/4.jpg)
![5](images/5.jpg)
![6](images/6.jpg)
![7](images/7.jpg)
![8](images/8.jpg)
![9](images/9.jpg)



