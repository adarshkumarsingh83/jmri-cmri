
// Enables the ESP8266 to connect to the local network (via WiFi)
#include <ESP8266WiFi.h>
// Allows us to connect to, and publish to the MQTT broker
#include <PubSubClient.h>

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "adarsh_radha_2G"; // ESP8266 do not support 5G wifi connection
const char* wifi_password = "******";
const char* mqtt_username = "adarsh";
const char* mqtt_password = "password";

// MQTT
const char* mqtt_server = "192.168.0.188";
const char* mqtt_topic = "/trains/track/#";
const String mqtt_topic_sensor = "/trains/track/sensor/";
const char* clientID = "JMRI_NODE_ESP8266_PUBLISHING_1";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient);

void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {
  String msg = getMessage(payload, length);
  String mqttTopic = String(topic);
  Serial.println();
  Serial.println("MQTT DATA::=> " + mqttTopic + " " + msg);
}

/*
   pushing the sensor data to the mqtt for jmri
*/
void publishSensorData(int sensorNo, String state) {
  String topic = mqtt_topic_sensor + String(sensorNo);
  Serial.print(topic+" "+state);
  Serial.println();
  client.publish(topic.c_str(), state.c_str());
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
bool sensorState = false;
void pushSensorsData() {
  delay(1000);
  if (sensorState) {
    publishSensorData(1, "ACTIVE");
    sensorState = false;
  } else {
    publishSensorData(1, "INACTIVE");
    sensorState = true;
  }
}

void setup() {

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

  pushSensorsData();

  delay(1000);
}
