/*
   ESP8266 (Adafruit HUZZAH) Mosquitto MQTT Subscribe Example
   Thomas Varnish (https://github.com/tvarnish), (https://www.instructables.com/member/Tango172)
   Made as part of my MQTT Instructable - "How to use MQTT with the Raspberry Pi and ESP8266"
*/
#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

const int ledPin = 0; // This code uses the built-in led for visual feedback that a message has been received

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "adarsh_radha_2G";
const char* wifi_password = "******";

// MQTT
const char* mqtt_server = "192.168.0.188";
const char* mqtt_topic = "/trains/track/light";
const char* clientID = "ESP8266_1";

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void subscribeMqttMessage(char* topic, byte* payload, unsigned int length) {

  String msg = getMessage(payload, length);
  Serial.println(msg);
  if (String(topic) == mqtt_topic) {
    if (msg == "ON") {
      digitalWrite(ledPin, HIGH);
    } else if (msg == "OFF") {
      digitalWrite(ledPin, LOW);
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
/*
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI IS NOT CONNECTED");
  } else {
    Serial.println("WIFI IS CONNECTED");
  }
*/
  // Connect to MQTT Server and subscribe to the topic
  //if (client.connect(clientID, mqtt_username, mqtt_password)) {
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
  // Remember to choose the correct Baudrate on the Serial monitor!
  // This is just for debugging purposes
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
  }
  else {
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
