#include "Config.h"
#include "Pca9685BoardManager.h"

Pca9685BoardManager pcaBoardManager;

void setup() {
  Serial.begin(115200);
  pcaBoardManager.initPca9685Boards();
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


void processCall(String message) {

  Serial.println("Message " + message);
  char type = message.charAt(0);
  message = message.substring(2);

  if (type == S) {
    String idNumber = message.substring(0, 5);
    int jmriId = atoi(idNumber.c_str());
    String signalLight1 = message.substring(0, 14);
    String boardNumber = signalLight1.substring(7, 8);
    String pinNumber = signalLight1.substring(10, 11);
    String value = signalLight1.substring(12, 14);
    int boardId = atoi(boardNumber.c_str());
    int pinId = atoi(pinNumber.c_str());
    //Serial.println("signalLight1 " + signalLight1);
    //doExecute(jmriId, boardId, pinId, value);

    if (value == ON) {
      pcaBoardManager.switchOn(boardId, pinId);
    } else {
      pcaBoardManager.switchOff( boardId, pinId);
    }

    String signalLight2 = message.substring(15, 29);
    idNumber = signalLight2.substring(0, 5);
    jmriId = atoi(idNumber.c_str());
    boardNumber = signalLight2.substring(7, 8);
    pinNumber = signalLight2.substring(10, 11);
    value = signalLight2.substring(12, 14);
    boardId = atoi(boardNumber.c_str());
    pinId = atoi(pinNumber.c_str());
    //Serial.println("signalLight2 " + signalLight2);
    //doExecute(jmriId, boardId, pinId, value);

    if (value == ON) {
      pcaBoardManager.switchOn(boardId, pinId);
    } else {
      pcaBoardManager.switchOff( boardId, pinId);
    }


    String signalLight3 = message.substring(30);
    idNumber = signalLight3.substring(0, 5);
    jmriId = atoi(idNumber.c_str());
    boardNumber = signalLight3.substring(7, 8);
    pinNumber = signalLight3.substring(10, 11);
    value = signalLight3.substring(12, 14);
    boardId = atoi(boardNumber.c_str());
    pinId = atoi(pinNumber.c_str());
    //Serial.println("signalLight3 " + signalLight3);
    //doExecute(jmriId, boardId, pinId, value);

    if (value == ON) {
      pcaBoardManager.switchOn(boardId, pinId);
    } else {
      pcaBoardManager.switchOff( boardId, pinId);
    }

  } else {
    String idNumber = message.substring(0, 5);
    int jmriId = atoi(idNumber.c_str());
    String boardNumber = message.substring(7, 8);
    String pinNumber = message.substring(10, 11);
    String value = message.substring(12, 14);
    int boardId = atoi(boardNumber.c_str());
    int pinId = atoi(pinNumber.c_str());
    doExecute(jmriId, boardId, pinId, value);

    if (type == T ) {
      if (value == THROWN) {
        pcaBoardManager.switchThrow(boardId, pinId);
      } else {
        pcaBoardManager.switchClose( boardId, pinId);
      }
    } else if ( type == L) {
      if (value == ON) {
        pcaBoardManager.switchOn(boardId, pinId);
      } else {
        pcaBoardManager.switchOff( boardId, pinId);
      }
    }
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
