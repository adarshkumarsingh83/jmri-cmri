

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

## To publish Data on mqtt 
### open a new terminal window 
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "CLOSED"
* mosquitto_pub -h localhost -t /trains/track/turnout/123 -r -m "THROWN" 

### with the User name and pwd 
* mosquitto_pub -h localhost -u username -P password -t /trains/track/turnout/1 -r -m "CLOSED"
* mosquitto_pub -h localhost -u username -P password -t /trains/track/turnout/1 -r -m "THROWN"  


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

---


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
### WITHOUT USERNAME AND PASSWORD 

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/1.png)

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/2.png)


### WITH USERNAME AND PASSWORD 

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/16.png)


### CREATING TURNOUT LIGHTS AND SENSORS IN PANELPRO 

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



# ESP8266/NODEMCU CLIENT FOR MOSQUITTO 

---

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/10.png)

```

// Enables the ESP8266 to connect to the local network (via WiFi)
#include <ESP8266WiFi.h>
// Allows us to connect to, and publish to the MQTT broker
#include <PubSubClient.h>

// This code uses the built-in led for visual feedback that a message has been received
const int ledPin = 0;

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "adarsh_radha_2G"; // ESP8266 donot support 5G wifi connection
const char* wifi_password = "*********";

// MQTT
const char* mqtt_server = "192.168.0.188";
const char* mqtt_topic = "/trains/track/#";
const char* mqtt_topic_light = "/trains/track/light/";
const char* mqtt_topic_turnout = "/trains/track/turnout/";
const char* mqtt_topic_sensor = "/trains/track/sensor/";
const char* clientID = "ESP8266_1";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);

void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {

  String msg = getMessage(payload, length);
  String mqttTopic = String(topic);
  Serial.println();
  Serial.println("MQTT DATA::=> "+mqttTopic+" "+msg);  

  if (mqttTopic.startsWith(mqtt_topic_light)) {
    String lightNumber = mqttTopic;
    lightNumber.replace(mqtt_topic_light, "");
    if (msg == "ON") {
      Serial.println();
      Serial.print("Light Number ");
      Serial.print(lightNumber + "  " + msg);
      Serial.println();
      digitalWrite(ledPin, HIGH);
    } else if (msg == "OFF") {
      Serial.println();
      Serial.print("Light Number ");
      Serial.print(lightNumber + "  " + msg);
      Serial.println();
      digitalWrite(ledPin, LOW);
    }
  } else if (mqttTopic.startsWith(mqtt_topic_turnout)) {
    String turnoutNumber = mqttTopic;
    turnoutNumber.replace(mqtt_topic_turnout, "");
    if (msg == "THROWN") {
      Serial.println("Turnout Number ");
      Serial.print(turnoutNumber + "  " + msg);
    } else if (msg == "CLOSED") {
      Serial.println();
      Serial.print("Turnout Number ");
      Serial.print(turnoutNumber + "  " + msg);
      Serial.println();
    }
  } else if (mqttTopic.startsWith(mqtt_topic_sensor)) {
    String sensorNumber = mqttTopic;
    sensorNumber.replace(mqtt_topic_sensor, "");
    if (msg == "ACTIVE") {
      Serial.println();
      Serial.print("Sensor Number ");
      Serial.print(sensorNumber + "  " + msg);
      Serial.println();
    } else if (msg == "INACTIVE") {
      Serial.println();
      Serial.print("Sensor Number ");
      Serial.print(sensorNumber + "  " + msg);
      Serial.println();
    }
  }
}

String getMessage(byte* message, unsigned int length) {
  String messageText;
  for (int i = 0; i < length; i++) {
    messageText += (char)message[i];
  }
  return messageText;
}

bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topic
  // if (client.connect(clientID)) { //uncomment when user name and pwd is not enable in mqtt
  if (client.connect(clientID, mqtt_username, mqtt_password)) {  // uncomment when user name and pwd is enable in mqtt
    client.subscribe(mqtt_topic);
    return true;
  } else {
    return false;
  }
}

void setup() {

  pinMode(ledPin, OUTPUT);

  // Switch the on-board LED off to start with
  digitalWrite(ledPin, HIGH);

  // Begin Serial on 115200
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // setCallback sets the function to be called when a message is received.
  client.setCallback(subscribeMqttMessage);
  if (mqttConnect()) {
    Serial.println("Connected Successfully to MQTT Broker!");
  } else {
    Serial.println("Connection Failed!");
  }
}

void loop() {
  // If the connection is lost, try to connect again
  if (!client.connected()) {
    mqttConnect();
  }
  // client.loop() just tells the MQTT client code to do what it needs to do itself (i.e. check for messages, etc.)
  client.loop();
  // Once it has done all it needs to do for this cycle, go back to checking if we are still connected.
  delay(1000);
}

```

### Connecting the Esp8266 with the Mosqutto mqtt server

![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/11.png)

### Connecting jmri panel pro with with the Mosqutto mqtt server
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/12.png)

### Configuring Turnout and testing it till Esp8266/nodemcu  
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/13.png)

### Configuring Light and testing it till Esp8266/nodemcu 
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/14.png)

### Configuring Sensors and testing it till Esp8266/nodemcu 
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/15.png)


### Testing with User name Pwd Configured MQTT with Esp8266/NODE MCU 
![img](/DOCUMENTS/JMRI-MOSQUITTO-MQTT/images/17.png)