

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
* w+q  // to save and exit the file 
* to run the scripty 
	* python start-mos.py 

### Stop script 
* vi stop-mos.py
```
import subprocess

subprocess.call('killall mosquitto',shell=True)
```
* esc //to stop inserting text to file
* w+q  // to save and exit the file 
* to run the scripty 
	* python stop-mos.py 

# JMRI WITH MQTT MOSQUITTO
* [JMRI DOC LINK ](https://www.jmri.org/help/en/html/hardware/mqtt/index.shtml)
