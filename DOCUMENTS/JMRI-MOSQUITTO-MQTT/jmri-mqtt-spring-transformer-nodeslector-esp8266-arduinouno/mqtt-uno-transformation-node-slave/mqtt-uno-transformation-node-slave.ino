#include "Config.h"
#include "Pca9685BoardManager.h"

String light;
String jId ;
String bId ;
String pId ;
String val;
int jmriId ;
int boardId ;
int pinId ;

Pca9685BoardManager pcaBoardManager;

void setup() {
  Serial.begin(115200);
  Serial.flush();
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

void displayData(String message) {
  Serial.println("Orignal Message  " + message);
  message = message.substring(2);
  Serial.println("Message After type removal  " + message);

  String light1 = message.substring(0, 14);
  message = message.substring(15);
  Serial.println("Message 1 " + light1);

  if (message.length() >= 14) {
    String light2 = message.substring(0, 14);
    message = message.substring(15);
    Serial.println("Message 2 " + light2);

    if (message.length() >= 14) {
      String light3 = message.substring(0, 14);
      message = message.substring(15);
      Serial.println("Message 3 " + light3);
    }
  }
}


void processCall(String msg) {

  Serial.println("Message " + msg);
  char type = msg.charAt(0);
  msg = msg.substring(2);

  if (type == S) {

    doExecute(msg);
    msg = msg.substring(15);

    if (msg.length() >= 14) {

      doExecute(msg);
      msg = msg.substring(15);

      if (msg.length() >= 14) {

        doExecute(msg);
      }
    }
  } else {

    jId = msg.substring(0, 5);
    bId = msg.substring(6, 8);
    pId = msg.substring(9, 11);
    val = msg.substring(12, 14);

    jmriId = atoi(jId.c_str());
    boardId = atoi(bId.c_str());
    pinId = atoi(pId.c_str());

    Serial.println("boardNumber " + bId);
    Serial.println("pinNumber " + pId);
    Serial.println("value " + val);

    doPrint(msg, jmriId, boardId, pinId, val);

    if (type == T ) {
      if (val == THROWN) {
        pcaBoardManager.switchThrow(boardId, pinId);
      } else {
        pcaBoardManager.switchClose( boardId, pinId);
      }
    } else if ( type == L) {
      if (val == ON) {
        pcaBoardManager.switchOn(boardId, pinId);
      } else {
        pcaBoardManager.switchOff( boardId, pinId);
      }
    }
  }
}

void doExecute(String msg) {
  light = msg.substring(0, 14);
  jId = light.substring(0, 5);
  bId = light.substring(6, 8);
  pId = light.substring(9, 11);
  val = light.substring(12, 14);

  jmriId = atoi(jId.c_str());
  boardId = atoi(bId.c_str());
  pinId = atoi(pId.c_str());

  Serial.println("boardNumber " + bId);
  Serial.println("pinNumber " + pId);
  Serial.println("value " + val);


  //doPrint(light,jmriId, boardId, pinId, val);

  if (val == ON) {
    pcaBoardManager.switchOn(boardId, pinId);
  } else {
    pcaBoardManager.switchOff( boardId, pinId);
  }

}

void doPrint(String input, int jmriId, int boardId, int pinId, String state) {
  Serial.println("Input " + input);
  Serial.print("Number " );
  Serial.print(jmriId );
  Serial.print(" Board Number ");
  Serial.print(boardId );
  Serial.print(" Pin Number ");
  Serial.print( pinId );
  Serial.println(" Value " + state);
}
