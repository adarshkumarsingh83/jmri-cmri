#include <ArduinoJson.h>

#define LIGHT "LIGHT"
#define TURNOUT "TURNOUT"
#define THROWN "THROWN"
#define CLOSED "CLOSED"
#define ON "ON"
#define OFF "OFF"

void processCall(String message) {
  Serial.println(message);
  DynamicJsonDocument jsonDocument(256);
  DeserializationError error = deserializeJson(jsonDocument, message);
  if (error) {
    Serial.print(F("ESP deserializeJson() failed: "));
    Serial.println(error.c_str());
    message = "";
    return;
  }

  String type = jsonDocument["type"];
  String number = jsonDocument["id"];
  String value = jsonDocument["value"];

  Serial.println(type + " " + number + " " + value);

  int id = atoi(jsonDocument["id"]);

  if (type == LIGHT) {

    if (value == ON) {
      Serial.println();
      Serial.print("Light Number " + number + "  " + value);
      Serial.println();
    } else if (value == OFF) {
      Serial.println();
      Serial.print("Light Number " + number + "  " + value);
      Serial.println();
    }

  } else if (type == TURNOUT) {

    if (id >= 2000 && id < 3000) { //all the turnout are started with 2000 onwards to 2999 address on jmri

      if (value == THROWN) {
        Serial.println();
        Serial.print("Turnout Number " + number + "  " + value);
        Serial.println();
      } else if (value == CLOSED) {
        Serial.println();
        Serial.print("Turnout Number " + number + "  " + value);
        Serial.println();
      }

    } else if (id >= 3000) { // all the signal are started with 3000 onwards address on jmri

      if (value == THROWN) {
        Serial.println();
        Serial.print("Signal Number " + number + " ON");
        Serial.println();
      } else if (value == CLOSED) {
        Serial.println();
        Serial.print("Signal Number " + number + " OFF");
        Serial.println();
      }

    }

  }
}


void setup() {
  Serial.begin(115200);
}


void loop() {
  // Monitor serial communication
  while (Serial.available()) {    
    processCall(Serial.readString());    
  }
  delay(200);
}
