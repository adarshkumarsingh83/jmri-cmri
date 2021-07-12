
// Enables the ESP8266 to connect to the local network (via WiFi)
#include <ESP8266WiFi.h>
// Allows us to connect to, and publish to the MQTT broker
#include <PubSubClient.h>

// This code uses the built-in led for visual feedback that a message has been received
const int ledPin = 0;

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "adarsh_radha_2G"; // ESP8266 donot support 5G wifi connection
const char* wifi_password = "******";

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
  if (client.connect(clientID)) {
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
