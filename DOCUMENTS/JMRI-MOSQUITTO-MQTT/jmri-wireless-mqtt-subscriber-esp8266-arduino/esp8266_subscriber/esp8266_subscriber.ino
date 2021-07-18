
// Enables the ESP8266 to connect to the local network (via WiFi)
#include <ESP8266WiFi.h>
// Allows us to connect to, and publish to the MQTT broker
#include <PubSubClient.h>
#include <Wire.h>

#define LIGHT "LIGHT"
#define TURNOUT "TURNOUT"
// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "adarsh_radha_2G"; // ESP8266 do not support 5G wifi connection
const char* wifi_password = "*******";
const char* mqtt_username = "adarsh";
const char* mqtt_password = "password";

// MQTT
const char* mqtt_server = "192.168.0.188"; // find this ip using ipconfig or check in router
const char* mqtt_topic = "/trains/track/#";
const char* mqtt_topic_light = "/trains/track/light/";
const char* mqtt_topic_turnout = "/trains/track/turnout/";
const char* clientID = "JMRI_SUBSCRIBER_NODE_ESP8266_1";

String payload = "";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);

void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {

  String mqttTopicValue = getMessage(payload, length);
  String mqttTopic = String(topic);
  Serial.println();
  Serial.println("MQTT DATA::=> " + mqttTopic + " " + mqttTopicValue);
  Serial.println();

  if (mqttTopic.startsWith(mqtt_topic_light)) {
    String lightNumberVar = mqttTopic;
    lightNumberVar.replace(mqtt_topic_light, "");
    pushDataToSlave(LIGHT, lightNumberVar, mqttTopicValue);
  } else if (mqttTopic.startsWith(mqtt_topic_turnout)) {
    String numberVar = mqttTopic;
    numberVar.replace(mqtt_topic_turnout, "");
    pushDataToSlave(TURNOUT, numberVar, mqttTopicValue);
  }
}

void pushDataToSlave(String type, String id, String value) {
  payload = "{\"type\":\"" + type + "\",\"id\":\"" + id + "\",\"value\":\"" + value + "\"}";
  Serial.println();
  Serial.println(payload);
  Serial.println();
  Wire.beginTransmission(8);
  Wire.write(payload.c_str());
  Wire.endTransmission();
}


/*
   converting message from mqtt bytes to string
*/
String getMessage(byte* message, unsigned int length) {
  String messageText;
  for (int i = 0; i < length; i++) {
    messageText += (char)message[i];
  }
  return messageText;
}

bool mqttConnect() {
  // Connect to MQTT Server and subscribe to the topic
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    client.subscribe(mqtt_topic);
    return true;
  } else {
    return false;
  }
}

void setup() {

  // Begin Serial on 115200
  Serial.begin(115200);
  Wire.begin(4, 5); //SDA, SCL
  
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
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
