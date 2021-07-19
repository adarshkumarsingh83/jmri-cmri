#include "CircularQueue.cpp"

#define THROWN "TH"
#define CLOSED "CL"
#define ON "ON"
#define OFF "OF"

const CircularQueue<String> queue = CircularQueue<String>(20, "mqtt-msg");

void processCall(String message) {
  Serial.println(message);
  message.trim();
  String number = message.substring(0, 4);
  String value = message.substring(5);

  //Serial.println(number + " - " + value);

  int id = atoi(number.c_str());

  if (id <= 2000) { //all the light are started with 1000 onwards to 1999 address on jmri
    if (value == ON) {
      Serial.println("Light Number " + number + "  " + value);
    } else if (value == OFF) {
      Serial.println("Light Number " + number + "  " + value);
    }

  } else if (id >= 2000 && id < 3000) { //all the turnout are started with 2000 onwards to 2999 address on jmri
    if (value == THROWN) {
      Serial.println("Turnout Number " + number + "  " + value);
    } else if (value == CLOSED) {
      Serial.println("Turnout Number " + number + "  " + value);
    }

  } else if (id >= 3000) { // all the signal are started with 3000 onwards address on jmri
    if (value == THROWN) {
      Serial.println("Signal Number " + number + " ON");
    } else if (value == CLOSED) {
      Serial.println("Signal Number " + number + " OFF");
    }
  }

}


void setup() {
  Serial.begin(115200);
}


void loop() {
  // Monitor serial communication
  while (Serial.available()) {
    String message = Serial.readString();
    if (message != "") {
      queue.push(message);
    }
  }

  while (!queue.isEmpty()) {
    processCall(queue.pop());
  }

  delay(200);
}
