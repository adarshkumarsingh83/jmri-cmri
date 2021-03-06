#include <ArduinoJson.h>
#include <Wire.h>

#define LIGHT "LIGHT"
#define TURNOUT "TURNOUT"
#define THROWN "THROWN"
#define CLOSED "CLOSED"
#define ON "ON"j
#define OFF "OFF"


String data = "";

void receiveEvent(int howMany) {

  while (0 < Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    data += c;
  }
  Serial.println(data);           /* print the request data */
  processCall(data);             /* to newline */
  data = "";
}


void setup() {
  Serial.begin(115200);
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}


void processCall(String command) {

  DynamicJsonDocument jsonDocument(256);
  DeserializationError error = deserializeJson(jsonDocument, command);
  if (error) {
    Serial.print(F("ESP deserializeJson() failed: "));
    Serial.println(error.c_str());
    data = "";
    return;
  }

  String type = jsonDocument["type"];
  int id = atoi(jsonDocument["id"]);
  String value = jsonDocument["value"];

  if (type == LIGHT) {

    if (value == ON) {
      Serial.println();
      Serial.print("Light Number ");
      Serial.print(id + "  " + value);
      Serial.println();
    } else if (value == OFF) {
      Serial.println();
      Serial.print("Light Number ");
      Serial.print(id + "  " + value);
      Serial.println();
    }

  } else if (type == TURNOUT) {

    if (id >= 2000 && id < 3000) { //all the turnout are started with 2000 onwards to 2999 address on jmri

      if (value == THROWN) {
        Serial.println();
        Serial.print("Turnout Number ");
        Serial.print(id + "  " + value);
        Serial.println();
      } else if (value == CLOSED) {
        Serial.println();
        Serial.print("Turnout Number ");
        Serial.print(id + "  " + value);
        Serial.println();
      }

    } else if (id >= 3000) { // all the signal are started with 3000 onwards address on jmri

      if (value == THROWN) {
        Serial.println();
        Serial.print("Signal Number ");
        Serial.print(id + " ON" );
        Serial.println();
      } else if (value == CLOSED) {
        Serial.println();
        Serial.print("Signal Number ");
        Serial.print(id + " OFF");
        Serial.println();
      }

    }

  }
}


void loop() {
  delay(200);
}
