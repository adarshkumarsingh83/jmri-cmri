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
* $ java -jar ./target/amt-jmri-mqtt-transformer.jar

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

### TO CONFIGURE THE MQTT FOR THE APLICATION 
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
    lightStartingAddress: 1000   #starting address of the light in whole layout its mandatory value 
    turnoutStartingAddress: 2000 #starting address of the turnout in whole layout its mandatory value 
    signalStartingAddress: 3000  #starting address of the signal in whole layout its mandatory value 
    nodes:
      -
        nodeId: 1                  # node id/name publish topic will be formed with this id only  
        lightStartAddress: 1000    # starting address of the light in node 1 ,if not configured then configure with 0 value 
        lightCount: 10             # no of light configured in node 1 ,if not configured then configure with 0 value 
        turnoutStartAddress: 2000  # starting address of the turnout in node 1 ,if not configured then configure with 0 value 
        turnoutCount: 15           # no of turnout configured in node 1 ,if not configured then configure with 0 value 
        signalStartAddress: 3000   # starting address of the signal in node 1 ,if not configured then configure with 0 value 
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
    lightStartingAddress: 1000 
    turnoutStartingAddress: 2000
    signalStartingAddress: 3000
    nodes:
      -
        nodeId: 1   
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
/amt/node/1/light/1000 OF

/amt/node/1/turnout/2000 TH
/amt/node/1/turnout/2000 CL

/amt/node/1/signal/3003 ON
/amt/node/1/signal/3002 OF
/amt/node/1/signal/3001 OF

/amt/node/1/signal/3003 OF
/amt/node/1/signal/3002 OF
/amt/node/1/signal/3001 OF

```