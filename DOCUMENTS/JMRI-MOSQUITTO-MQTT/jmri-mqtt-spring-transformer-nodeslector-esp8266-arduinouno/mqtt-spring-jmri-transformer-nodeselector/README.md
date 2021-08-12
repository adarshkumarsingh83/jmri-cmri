# JMRI MQTT DATA TRANSFORMER NODE SELECTOR APPLICATION 

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
* $ java -jar ./target/amt-jmri-mqtt-transformer.jar

### To pass the customized configuration file 
* $ java -jar ./target/amt-jmri-mqtt-transformer.jar --spring.config.location=classpath:/application.properties,classpath:/application.yaml

## TO ENABLE JMRI MQTT DATA ENDPOINTS 
> ENABLE THE PROPERTIES in  src/main/resources/application.properties
```
## TO ENABLE THE REST API ENDPOINT FOR SERVING DATA  
amt.mqtt.transform.endpoints.enabled=false
## REST API ENDPOINT CACHE SIZE 
amt.mqtt.transform.endpoints.store.size=50


### ENABLE EITHER OF ONE OUTPUT TYPE 
### TRIPLE OUTPUT SIGNAL OUTPUT
#amt.output.signal.joiner=3
### DUAL OUTPUT SIGNAL OUTPUT
# amt.output.signal.joiner=2
### SIGNAL OUTPUT SIGNAL OUTPUT
amt.output.signal.joiner=1
```

### TO ACCESS THE MQTT DATA VIA END POINTS 
> curl -X GET http://localhost:8090/amt/node/[nodeId]
* curl -X GET http://localhost:8090/amt/node/1


## TO ENABLE THE PUBLISHING BACK TO THE MQTT 
> ENABLE THE PROPERTIES in  src/main/resources/application.properties
```
amt.mqtt.transform.publish=true
```

### TO CONFIGURE THE MQTT FOR THE APPLICATION 
```
# Custom property mqtt configuration
mqtt-properties:
  host: tcp://localhost:1883                        #mqtt host and port 
  clientId: adarsh-model-trains-transformer-        #client id for the application for mqtt 
  username: adarsh                                  #mqtt username
  password: password                                #mqtt password
  topicSub: /trains/track/#                         #mqtt jmri root topic to subscribe  
  lightTopic: /trains/track/light/                  #mqtt jmri light topic to subscribe  
  turnoutTopic: /trains/track/turnout/              #mqtt jmri turnout topic to subscribe  
  signalTopic: /trains/track/signalhead/            #mqtt jmri signalhead topic to subscribe
  topicPub: /amt/node/                              #application publish topic prefix 
  cleanSession: true                                #session clearing config 
  connectionTimeout: 300                            #connection timeout config 
  keepAliveInterval: 60                             #connection keepalive config 
  automaticReconnect: true                          #connection automatic reconnected when disconnected if true 

```

## TO CONFIGURING THE NODES DATA ON APPLICATION 
> CONFIGURE THE VALUES in  src/main/resources/application.yaml
```
node:
  configurations:
    lightStartingAddress: 10000   #starting address of the light in whole layout its mandatory value 
    turnoutStartingAddress: 20000 #starting address of the turnout in whole layout its mandatory value 
    signalStartingAddress: 30000  #starting address of the signal in whole layout its mandatory value 
    nodes:
      -
        nodeId: 1                  # node id/name publish topic will be formed with this id only
        turnoutBoardCount: 3       # total number of pca9685 configured for turnouts in arduino node
        lightBoardCount: 6         # total number of pca9685 configured for signal and lights in arduino node
        lightStartAddress: 10000    # starting address of the light in node 1 ,if not configured then configure with 0 value 
        lightCount: 10             # no of light configured in node 1 ,if not configured then configure with 0 value 
        turnoutStartAddress: 20000  # starting address of the turnout in node 1 ,if not configured then configure with 0 value 
        turnoutCount: 15           # no of turnout configured in node 1 ,if not configured then configure with 0 value 
        signalStartAddress: 30000   # starting address of the signal in node 1 ,if not configured then configure with 0 value 
        signalCount: 37            # no of signal configured in node 1 ,if not configured then configure with 0 value  
                                   # every light address in jmri for particular node that is the count 
                                   # every led in signal is having one count so if 3 led in signal count is 3
                                   # if signal is having 2 light red and green then 2 will be count for signal 
```
## samples which is configured by default 
```
# Custom property for nodes configuration
node:
  configurations:
    lightStartingAddress: 10000
    turnoutStartingAddress: 20000
    signalStartingAddress: 30000
    nodes:
      -
        nodeId: 1
        lightStartAddress: 10000
        lightCount: 10
        turnoutStartAddress: 20000
        turnoutCount: 15
        signalStartAddress: 30000
        signalCount: 36
        turnoutBoardCount: 3
        lightBoardCount: 3
      -
        nodeId: 2
        lightStartAddress: 10100
        lightCount: 27
        turnoutStartAddress: 20100
        turnoutCount: 48
        signalStartAddress: 30100
        signalCount: 81
        turnoutBoardCount: 6
        lightBoardCount: 7
      -
        nodeId: 3
        lightStartAddress: 10200
        lightCount: 7
        turnoutStartAddress: 20200
        turnoutCount: 27
        signalStartAddress: 30200
        signalCount: 87
        turnoutBoardCount: 4
        lightBoardCount: 6
      -
        nodeId: 4
        lightStartAddress: 10300
        lightCount: 23
        turnoutStartAddress: 20300
        turnoutCount: 10
        signalStartAddress: 30300
        signalCount: 24
        turnoutBoardCount: 2
        lightBoardCount: 3
      -
        nodeId: 5
        lightStartAddress: 10400
        lightCount: 45
        turnoutStartAddress: 20400
        turnoutCount:
        signalStartAddress: 30400
        signalCount: 80
        turnoutBoardCount: 10
        lightBoardCount: 8
      -
        nodeId: 6
        lightStartAddress: 10500
        lightCount: 10
        turnoutStartAddress: 20500
        turnoutCount: 15
        signalStartAddress: 30500
        signalCount: 45
        turnoutBoardCount: 2
        lightBoardCount: 4
      -
        nodeId: 7
        lightStartAddress: 10600
        lightCount: 12
        turnoutStartAddress: 20600
        turnoutCount: 48
        signalStartAddress: 30600
        signalCount: 80
        turnoutBoardCount: 6
        lightBoardCount: 6
      -
        nodeId: 8
        lightStartAddress: 10700
        lightCount: 7
        turnoutStartAddress: 20700
        turnoutCount: 21
        signalStartAddress: 30700
        signalCount: 87
        turnoutBoardCount: 3
        lightBoardCount: 6
      -
        nodeId: 9
        lightStartAddress: 10800
        lightCount: 23
        turnoutStartAddress: 20800
        turnoutCount: 10
        signalStartAddress: 30800
        signalCount: 24
        turnoutBoardCount: 3
        lightBoardCount: 3
      -
        nodeId: 10
        lightStartAddress: 10900
        lightCount: 45
        turnoutStartAddress: 20900
        turnoutCount: 23
        signalStartAddress: 30900
        signalCount: 80
        turnoutBoardCount: 3
        lightBoardCount: 8
```

### To subscribe the mqtt application error topic 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/erros/#'

### To subscribe the mqtt topic where application will publish data after transformation  
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/node/#'
```
/amt/node/1/light/ L:10001:05:04:ON
/amt/node/1/light/ L:10001:05:04:OF
/amt/node/1/light/ L:10002:05:05:ON
/amt/node/1/light/ L:10002:05:05:OF

/amt/node/1/turnout/ T:20001:00:00:TH
/amt/node/1/turnout/ T:20001:00:01:CL

/amt/node/1/signal/ S:30003:03:02:ON|30002:03:01:OF|30001:03:00:OF
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:ON|30001:03:00:OF
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:OF|30001:03:00:ON
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:OF|30001:03:00:OF

```