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
```

### TO ACCESS THE MQTT DATA VIA END POINTS 
> curl -X GET http://localhost:8090/amt/node/[nodeId]
* curl -X GET http://localhost:8090/amt/node/1


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
    turnoutStartingAddress: 10000 #starting address of the turnout in whole layout its mandatory value 
    signal2LStartingAddress: 20000  #starting address of the 2 light signal in whole layout its mandatory value 
    signal3LStartingAddress: 30000  #starting address of the 3 light signal in whole layout its mandatory value 
    nodes:
      -
        nodeId: 1                                   # node id/name publish topic will be formed with this id only
        turnoutBoardCount: 3                        # total number of pca9685 configured for turnouts in arduino node
        lightBoardCount: 6                          # total number of pca9685 configured for signal and lights in arduino node
        lightPublishTopic: /amt/node/1/light/       # light publish topic after transformation 
        turnoutPublishTopic: /amt/node/1/turnout/   # turnout publish topic after transformation 
        signalPublishTopic: /amt/node/1/signal/     # signal publish topic after transformation 
        apiEndpointCacheSize: 10                    # api enpoint cache size 
        lightStartAddress: 1000                     # starting address of the light in node 1 ,if not configured then configure with 0 value 
        lightCount: 10                              # no of light configured in node 1 ,if not configured then configure with 0 value 
        turnoutStartAddress: 10000                  # starting address of the turnout in node 1 ,if not configured then configure with 0 value 
        turnoutCount: 15                            # no of turnout configured in node 1 ,if not configured then configure with 0 value 
        signal2LStartAddress: 20000                 # starting address of the 2 light signal in node 1 ,if not configured then configure with 0 value
        signal2LCount: 64                           # no of signal configured in node 1 ,if not configured then configure with 0 value  
        signal3LStartAddress: 30000                 # starting address of the 3 light signal in node 1 ,if not configured then configure with 0 value 
        signal3LCount: 37                           # no of signal configured in node 1 ,if not configured then configure with 0 value  
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
    turnoutStartingAddress: 10000
    signal2LStartingAddress: 20000
    signal3LStartingAddress: 30000
    nodes:
      -
        nodeId: 1
        lightStartAddress: 1000
        lightCount: 5                    # 1 ins for each light
        turnoutStartAddress: 10000
        turnoutCount: 16                 # 2 pins for each turnout (16 * 2) /16 => 16
        signal2LStartAddress: 20000
        signal2LCount: 64                # 2 pins for each signals light  total 16 turnout and every turnout has 2 splitter track (16 * 2 * 2) => 64
        signal3LStartAddress: 30000
        signal3LCount: 30                # 3 pins for each signals (10 * 3) => 30
        turnoutBoardCount: 2             # (turnoutCount * 2)/16 :=>  (16 * 2) / 16 => 2
        lightBoardCount: 9               # (lightCount + signal2LCount + signal3LCount) /16 :=>  (5+32+30)/16 =>  5
        lightPublishTopic: /amt/node/1/light/
        turnoutPublishTopic: /amt/node/1/turnout/
        signalPublishTopic: /amt/node/1/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 2
        lightStartAddress: 1100
        lightCount: 5
        turnoutStartAddress: 10100
        turnoutCount: 15
        signal2LStartAddress: 20100
        signal2LCount: 60
        signal3LStartAddress: 30100
        signal3LCount: 30
        turnoutBoardCount: 2
        lightBoardCount: 7
        lightPublishTopic: /amt/node/2/light/
        turnoutPublishTopic: /amt/node/2/turnout/
        signalPublishTopic: /amt/node/2/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 3
        lightStartAddress: 1200
        lightCount: 7
        turnoutStartAddress: 10200
        turnoutCount: 15
        signal2LStartAddress: 20200
        signal2LCount: 60
        signal3LStartAddress: 30200
        signal3LCount: 18
        turnoutBoardCount: 2
        lightBoardCount: 6
        lightPublishTopic: /amt/node/3/light/
        turnoutPublishTopic: /amt/node/3/turnout/
        signalPublishTopic: /amt/node/3/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 4
        lightStartAddress: 1300
        lightCount: 23
        turnoutStartAddress: 10300
        turnoutCount: 10
        signal2LStartAddress: 20300
        signal2LCount: 10
        signal3LStartAddress: 30300
        signal3LCount: 24
        turnoutBoardCount: 2
        lightBoardCount: 3
        lightPublishTopic: /amt/node/4/light/
        turnoutPublishTopic: /amt/node/4/turnout/
        signalPublishTopic: /amt/node/4/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 5
        lightStartAddress: 1400
        lightCount: 45
        turnoutStartAddress: 10400
        turnoutCount: 10
        signal2LStartAddress: 20400
        signal2LCount: 10
        signal3LStartAddress: 30400
        signal3LCount: 80
        turnoutBoardCount: 10
        lightBoardCount: 8
        lightPublishTopic: /amt/node/5/light/
        turnoutPublishTopic: /amt/node/5/turnout/
        signalPublishTopic: /amt/node/5/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 6
        lightStartAddress: 1500
        lightCount: 10
        turnoutStartAddress: 10500
        turnoutCount: 15
        signal2LStartAddress: 20500
        signal2LCount: 10
        signal3LStartAddress: 30500
        signal3LCount: 45
        turnoutBoardCount: 2
        lightBoardCount: 4
        lightPublishTopic: /amt/node/6/light/
        turnoutPublishTopic: /amt/node/6/turnout/
        signalPublishTopic: /amt/node/6/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 7
        lightStartAddress: 1600
        lightCount: 12
        turnoutStartAddress: 10600
        turnoutCount: 48
        signal2LStartAddress: 20600
        signal2LCount: 10
        signal3LStartAddress: 30600
        signal3LCount: 80
        turnoutBoardCount: 6
        lightBoardCount: 6
        lightPublishTopic: /amt/node/7/light/
        turnoutPublishTopic: /amt/node/7/turnout/
        signalPublishTopic: /amt/node/7/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 8
        lightStartAddress: 1700
        lightCount: 7
        turnoutStartAddress: 10700
        turnoutCount: 21
        signal2LStartAddress: 20700
        signal2LCount: 10
        signal3LStartAddress: 30700
        signal3LCount: 87
        turnoutBoardCount: 3
        lightBoardCount: 6
        lightPublishTopic: /amt/node/8/light/
        turnoutPublishTopic: /amt/node/8/turnout/
        signalPublishTopic: /amt/node/8/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 9
        lightStartAddress: 1800
        lightCount: 23
        turnoutStartAddress: 10800
        turnoutCount: 10
        signal2LStartAddress: 20800
        signal2LCount: 10
        signal3LStartAddress: 30800
        signal3LCount: 24
        turnoutBoardCount: 3
        lightBoardCount: 3
        lightPublishTopic: /amt/node/9/light/
        turnoutPublishTopic: /amt/node/9/turnout/
        signalPublishTopic: /amt/node/9/signal/
        apiEndpointCacheSize: 10
      -
        nodeId: 10
        lightStartAddress: 1900
        lightCount: 45
        turnoutStartAddress: 10900
        turnoutCount: 23
        signal2LStartAddress: 20900
        signal2LCount: 10
        signal3LStartAddress: 30900
        signal3LCount: 80
        turnoutBoardCount: 3
        lightBoardCount: 8
        lightPublishTopic: /amt/node/10/light/
        turnoutPublishTopic: /amt/node/10/turnout/
        signalPublishTopic: /amt/node/10/signal/
        apiEndpointCacheSize: 10

```
### To subscribe the mqtt jmri topic with original jmri messages  
* $  mosquitto_sub -h localhost -u adarsh -P password -v -t '/trains/track/#'

### To subscribe the mqtt application error topic 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/erros/#'

### To subscribe the spring transformer connection  error topic 
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/transformer/#'

### To subscribe the mqtt topic where application will publish data after transformation  
* $ mosquitto_sub -h localhost -u adarsh -P password -v -t '/amt/node/#'
```
/amt/node/1/light/ L:1001:05:04:ON
/amt/node/1/light/ L:1001:05:04:OF

/amt/node/1/turnout/ T:10001:00:00:TH
/amt/node/1/turnout/ T:10001:00:01:CL

/amt/node/1/signal/ S:20004:03:02:ON|20005:03:01:OF
/amt/node/1/signal/ S:20004:03:02:OF|20005:03:01:ON
/amt/node/1/signal/ S:20004:03:02:OF|20005:03:01:OF

/amt/node/1/signal/ S:30003:03:02:ON|30002:03:01:OF|30001:03:00:OF
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:ON|30001:03:00:OF
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:OF|30001:03:00:ON
/amt/node/1/signal/ S:30003:03:02:OF|30002:03:01:OF|30001:03:00:OF

```