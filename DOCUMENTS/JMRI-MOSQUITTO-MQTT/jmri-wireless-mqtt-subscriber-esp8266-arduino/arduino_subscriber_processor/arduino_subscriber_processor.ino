#include <ArduinoJson.h>

String message = "";
bool messageReady = false;

#define THROWN "THROWN"
#define CLOSED "CLOSED"
#define ON "ON"
#define OFF "OFF"

const char* mqtt_topic_light = "/trains/track/light/";
const char* mqtt_topic_turnout = "/trains/track/turnout/";

void setup() {
  Serial.begin(115200);
}

void loop() {

  // Monitor serial communication
  while (Serial.available()) {
    message = Serial.readString();
    messageReady = true;
  }

  // Only process message if there's one
  if (messageReady) {

    // The only messages we'll parse will be formatted in JSON
    DynamicJsonDocument doc(1024); // ArduinoJson version 6+
    // Attempt to deserialize the message
    DeserializationError error = deserializeJson(doc, message);
    if (error) {
      Serial.print(F("Uno deserializeJson() failed: "));
      Serial.println(error.c_str());
      messageReady = false;
      return;
    }


    if (doc["mqttTopic"] != "" && doc["mqttTopicValue"]) {

      String mqttTopic = doc["mqttTopic"];
      String mqttTopicValue = doc["mqttTopicValue"];

      if (mqttTopic.startsWith(mqtt_topic_light)) {

        String lightNumberVar = mqttTopic;
        lightNumberVar.replace(mqtt_topic_light, "");
        int lightNumber = lightNumberVar.toInt();

        if (mqttTopicValue == ON) {
          Serial.println();
          Serial.print("Light Number ");
          Serial.print(lightNumberVar + "  " + mqttTopicValue);
          Serial.println();
        } else if (mqttTopicValue == OFF) {
          Serial.println();
          Serial.print("Light Number ");
          Serial.print(lightNumberVar + "  " + mqttTopicValue);
          Serial.println();
        }

      } else if (mqttTopic.startsWith(mqtt_topic_turnout)) {

        String numberVar = mqttTopic;
        numberVar.replace(mqtt_topic_turnout, "");
        int number = numberVar.toInt();

        if (number >= 2000 && number < 3000) { //all the turnout are started with 2000 onwards to 2999 address on jmri

          if (mqttTopicValue == THROWN) {
            Serial.println();
            Serial.print("Turnout Number ");
            Serial.print(numberVar + "  " + mqttTopicValue);
            Serial.println();
          } else if (mqttTopicValue == CLOSED) {
            Serial.println();
            Serial.print("Turnout Number ");
            Serial.print(numberVar + "  " + mqttTopicValue);
            Serial.println();
          }

        } else if (number >= 3000) { // all the signal are started with 3000 onwards address on jmri

          if (mqttTopicValue == THROWN) {
            Serial.println();
            Serial.print("Signal Number ");
            Serial.print(numberVar + " ON" );
            Serial.println();
          } else if (mqttTopicValue == CLOSED) {
            Serial.println();
            Serial.print("Signal Number ");
            Serial.print(numberVar + " OFF");
            Serial.println();
          }

        }

      }
       serializeJson(doc, Serial);
    }
  }
  messageReady = false;
}
