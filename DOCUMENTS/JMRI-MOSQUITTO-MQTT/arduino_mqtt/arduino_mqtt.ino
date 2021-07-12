
// api download link https://pubsubclient.knolleary.net/
// api doucmentation link https://pubsubclient.knolleary.net/api


#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

long lastMsg = 0;

// WIFI SSID/Password
 //const char* ssid = "REPLACE_WITH_YOUR_SSID";
  char* ssid = "adarsh_radha_2G";
 //const char* password = "REPLACE_WITH_YOUR_PASSWORD";
  char* password = "******";

// MQTT Broker IP address, 
// On mac $ ipconfig getifaddr en0:
//const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";
const char* mqtt_server = "192.168.0.188";

// MQTT topics for reading and writing data 
//const char* subscriberTopicChannel = "esp32/output";
const char* subscriberTopicChannel = "/trains/track/light";
//const char* publisherTopicChannel = "esp32/input";
const char* publisherTopicChannel = "/trains/track/light";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.println();
  // If a message is received on the topic ,
  if (String(topic) == subscriberTopicChannel) {
     String msg = getMessage(message,length);
     Serial.println(msg);
  }
}

 String getMessage(byte* message,int length) {
  String messageText;
  for (int i = 0; i < length; i++) {
    messageText += (char)message[i];
  }
  return messageText;
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266_1")) {
      Serial.println("connected");
      // Subscribe to Mqtt topics 
      client.subscribe(subscriberTopicChannel);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");      
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

}

void loop() {
  if (!client.connected()) {
      reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000) { 
    lastMsg = now;
  
    //client.publish(publisherTopicChannel, "DATA TO PUBLISH TO JMRI");
  }
}
