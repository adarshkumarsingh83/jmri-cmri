#include "Config.h"


void processCall(String message) {

  Serial.println("Message " + message);

  String idNumber = message.substring(0, 5);
  int jmriId = atoi(idNumber.c_str());
  if (jmriId >=  SIGNAL_START_ADDRESS) {
    
    String signalLight1 = message.substring(0, 14);
    
    //Serial.println("signalLight1 " + signalLight1);

    String boardNumber = signalLight1.substring(7, 8);
    String pinNumber = signalLight1.substring(10, 11);
    String value = signalLight1.substring(12);
    int boardId = atoi(boardNumber.c_str());
    int pinId = atoi(pinNumber.c_str());
    doExecute(jmriId, boardId, pinId, value);

    String signalLight2 = message.substring(15, 29);

    //Serial.println("signalLight2 " + signalLight2);

    idNumber = signalLight2.substring(0, 5);
    jmriId = atoi(idNumber.c_str());
    boardNumber = signalLight2.substring(7, 8);
    pinNumber = signalLight2.substring(10, 11);
    value = signalLight2.substring(12);
    boardId = atoi(boardNumber.c_str());
    pinId = atoi(pinNumber.c_str());
    doExecute(jmriId, boardId, pinId, value);

    String signalLight3 = message.substring(30);

    //Serial.println("signalLight3 " + signalLight3);
    
    idNumber = signalLight3.substring(0, 5);
    jmriId = atoi(idNumber.c_str());
    boardNumber = signalLight3.substring(7, 8);
    pinNumber = signalLight3.substring(10, 11);
    value = signalLight3.substring(12);
    boardId = atoi(boardNumber.c_str());
    pinId = atoi(pinNumber.c_str());
    doExecute(jmriId, boardId, pinId, value);

  } else {
    String boardNumber = message.substring(7, 8);
    String pinNumber = message.substring(10, 11);
    String value = message.substring(12);
    int boardId = atoi(boardNumber.c_str());
    int pinId = atoi(pinNumber.c_str());
    doExecute(jmriId, boardId, pinId, value);
  }

}

void doExecute(int jmriId, int boardId, int pinId, String state) {
  Serial.print("Number " );
  Serial.print(jmriId );
  Serial.print(" Board Number ");
  Serial.print(boardId );
  Serial.print(" Pin Number ");
  Serial.print( pinId );
  Serial.println(" Value " + state);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Monitor serial communication
  while (Serial.available()) {
    String message = Serial.readString();
    if (message != "") {
      processCall(message);
    }
  }
  delay(200);
}
