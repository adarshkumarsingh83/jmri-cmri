# JMRI MQTT DATA TRANSFORMER APPLICATION 

> Jmri will push the data to the mqtt 
> transformer application configured with nodes and its details like no of turnout, no of signals, no of light in the node
> transformer application will read the data from mqtt topics which is pushed by jmri and transform that data 
> and push back to the mqtt node wise, also store in end points cache if enabled for serving data via rest endpoints   
> topics for each esp8266 node will have only relevant data only 
> this will reduce the processing on the esp8266 so that it can handle node specific data properly.

----

### To build this application 
* $ mnvn clean package 

### To Run this application 
* $ mvn spring-boot:run 

### To Run Executable jar of application 
* $ java -jar ./target/mqtt-jmri-transformer-0.0.1-SNAPSHOT.jar

## TO ENABLE JMRI MQTT DATA ENDPOINTS 
> ENABLE THE PROPERTIES in  src/main/resources/application.properties
```
# for enabling the endpoints data 
amt.mqtt.transform.endpoints.enabled=true

# storage cache capacity for the enpoints 
amt.mqtt.transform.endpoints.store.size=50
```

### TO ACCESS THE MQTT DATA VIA END POINTS 
> curl -X GET http://localhost:8090/amt/node/[nodeId]
* curl -X GET http://localhost:8090/amt/node/1


## TO ENABLE THE PUBLISHING BACK TO THE MQTT 
> ENABLE THE PROPERTIES in  src/main/resources/application.properties
```
amt.mqtt.transform.publish=true
```

## TO CONFIGURING THE NODES DATA ON APPLICATION 
> CONFIGURE THE VALUES in  src/main/resources/application.yaml
```
node:
  configurations:
    nodes:
      -
        nodeId: 1   # node id/name publish topic will be formed with this id only  
        lightStartAddress: 1000    # starting address of the light in node 1
        lightCount: 10             # no of light configured in node 1
        turnoutStartAddress: 2000  # starting address of the turnout in node 1
        turnoutCount: 15           # no of turnout configured in node 1
        signalStartAddress: 3000   # starting address of the signal in node 1
        signalCount: 37            # no of signal configured in node 1 
                                   # every light address in jmri for particular node that is the count 
                                   # every led in signal is having one count so if 3 led in signal count is 3
                                   # if signal is having 2 light red and green then 2 will be count for signal 
```
## samples which is configured by default 
```
# Custom property for nodes configuration
node:
  configurations:
    nodes:
      -
        nodeId: 1   #node id/name publish topic will be formed with this id only  
        lightStartAddress: 1000  
        lightCount: 10
        turnoutStartAddress: 2000
        turnoutCount: 15
        signalStartAddress: 3000
        signalCount: 37
      -
        nodeId: 2
        lightStartAddress: 1100
        lightCount: 27
        turnoutStartAddress: 2100
        turnoutCount: 48
        signalStartAddress: 3100
        signalCount: 80
      -
        nodeId: 3
        lightStartAddress: 1200
        lightCount: 7
        turnoutStartAddress: 2200
        turnoutCount: 27
        signalStartAddress: 3200
        signalCount: 87
      -
        nodeId: 4
        lightStartAddress: 1300
        lightCount: 23
        turnoutStartAddress: 2300
        turnoutCount: 10
        signalStartAddress: 3300
        signalCount: 24
      -
        nodeId: 5
        lightStartAddress: 1400
        lightCount: 45
        turnoutStartAddress: 2400
        turnoutCount: 78
        signalStartAddress: 3400
        signalCount: 80
      -
        nodeId: 6
        lightStartAddress: 1500
        lightCount: 10
        turnoutStartAddress: 2500
        turnoutCount: 15
        signalStartAddress: 3500
        signalCount: 37
      -
        nodeId: 7
        lightStartAddress: 1600
        lightCount: 27
        turnoutStartAddress: 2600
        turnoutCount: 48
        signalStartAddress: 3600
        signalCount: 80
      -
        nodeId: 8
        lightStartAddress: 1700
        lightCount: 7
        turnoutStartAddress: 2700
        turnoutCount: 27
        signalStartAddress: 3700
        signalCount: 87
      -
        nodeId: 9
        lightStartAddress: 1800
        lightCount: 23
        turnoutStartAddress: 2800
        turnoutCount: 10
        signalStartAddress: 3800
        signalCount: 24
      -
        nodeId: 10
        lightStartAddress: 1900
        lightCount: 45
        turnoutStartAddress: 2900
        turnoutCount: 78
        signalStartAddress: 3900
        signalCount: 80
```


### To run the mqtt where application will publish data 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/node/#'
```
/amt/node/1/light/1000 ON
/amt/node/1/light/1000 OFF

/amt/node/1/turnout/2000 THROWN
/amt/node/1/turnout/2000 CLOSE

/amt/node/1/signal/3003 ON
/amt/node/1/signal/3002 OFF
/amt/node/1/signal/3001 OFF

/amt/node/1/signal/3003 OFF
/amt/node/1/signal/3002 OFF
/amt/node/1/signal/3001 OFF

```



---

# [mosquitto mqtt](https://mosquitto.org/)

## To install brew 
$ /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

## To install mosquitto
$ brew install mosquitto


## doucmentation 
* [documentation](https://mosquitto.org/man/mosquitto-8.html)

---

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

---

## To Create User and pwd 
* create a file passwordfile.txt 
```
adarsh:password
```
* $ mosquitto_passwd -U passwordfile.txt 
* this will convert the plane pwd into the encrypted into the passwordfile.txt file 

### Example 
```
$ vi passwordfile.txt
$ cat passwordfile.txt 

adarsh:endless

$ mosquitto_passwd -U passwordfile.txt
$ cat passwordfile.txt 

adarsh:$7$101$wwBOuczh60K8AdjY$w9xVRzB02kNu64+cof8BNeBv/vbjQM9m+ey9G1B6TIxQmYZxrKwnR9L4v6e87bL4SwMgl/L98Qg8mnef9GKhhw==
```


### creating new pwd file pwd will be prompt once cmd is executed 
* $ mosquitto_passwd -c passwordfile.txt user_name 
```
$ Password:
$ Reenter password:
```

### appending into the exisisting pwd file 
* $ mosquitto_passwd -b passwordfile.txt user_name password 
* $ cat passwordfile.txt


## Configuring the user and pwd in to the mosquitto.conf file 
* $ vi mosquitto.conf
* press i for insert then copy paste below content
```
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous false         #Allows JMRI to subscribe without an ID or password
password_file ./passwordfile.txt

```
* esc //to stop inserting text to file
* :w+q // to save and exit the file


### Example 
```
$ mkdir mos-config
$ cd mos-config/

$ vi passwordfile.txt
$ cat passwordfile.txt 

adarsh:endless

$ mosquitto_passwd -U passwordfile.txt
$ cat passwordfile.txt 

adarsh:$7$101$wwBOuczh60K8AdjY$w9xVRzB02kNu64+cof8BNeBv/vbjQM9m+ey9G1B6TIxQmYZxrKwnR9L4v6e87bL4SwMgl/L98Qg8mnef9GKhhw==

$  vi mosquitto.conf
-----------------------------------------------------------------------
log_type all                 #Equivalent to setting -v (verbose mode)
listener 1883                #To ensure listening on the appropriate port
allow_anonymous false         #Allows JMRI to subscribe without an ID or password
password_file ./passwordfile.txt
-----------------------------------------------------------------------


$ vi start-pwd-mos.py
-----------------------
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c ./mosquitto.conf',shell=True)
-----------------------

$ python start-pwd-mos.py

or 

$ /usr/local/sbin/mosquitto -c mosquitto.conf
```

---


## Start with Configuration  
* To Run with Default Configuration 
	* $ /usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf
* To Run with Custom Configuration 
	* $ /usr/local/sbin/mosquitto -c ./mosquitto.conf

## To subscribe data on mqtt 
### open a new terminal window 
* mosquitto_sub -h localhost -v -t '/trains/#'

### with the User name and pwd 
* mosquitto_sub -h localhost -u username -P password -v -t '/trains/#'

### create python executable  
* $ vi sub.py
```
import subprocess

subprocess.call('mosquitto_sub -h localhost -u adarsh -P password -v -t /trains/#',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
  * python sub.py 

## To publish Data on mqtt 
### open a new terminal window 
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "CLOSED"
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "THROWN" 

### with the User name and pwd 
* mosquitto_pub -h localhost -u username -P password -t /trains/track/turnout/1 -r -m "CLOSED"
* mosquitto_pub -h localhost -u username -P password -t /trains/track/turnout/1 -r -m "THROWN"  


## python script for start and stop the mosquitto
### Start script with default configuration 
* vi start-mos.py
```
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
	* python start-mos.py 

### Start script with custom configuration 
* vi start-cust-mos.py
```
import subprocess

subprocess.call('/usr/local/sbin/mosquitto -c ./mosquitto.conf',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
	* python start-cust-mos.py


### Stop script 
* vi stop-mos.py
```
import subprocess

subprocess.call('killall mosquitto',shell=True)
```
* esc //to stop inserting text to file
* :w+q  // to save and exit the file 
* to run the script 
	* python stop-mos.py 

----