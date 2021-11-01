
#include "Config.h"

int i = 0;
int pinNo = -1;
bool exectuion = false;
long temp;
BoardPin boardSlot;

void setup() {
  Serial.begin(MESSAGE_BROAD_RATE);
  Serial.flush();
}

void loop() {
  delay(DELEY_TIME);
  if (!exectuion) {


    for (i = 1; i <= lightCount; i++) {
      temp = i + lightStartAddress;
      Serial.print("light On  input ");
      Serial.print(temp);
      generatePin(temp, ON);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();

      Serial.print("light Off input ");
      Serial.print(temp);
      generatePin(temp, OFF);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();
    }
    Serial.println();
    for (i = 1; i <= signal2LedCount; i++) {
      temp = i + signal2LedStartAddress;
      Serial.print("2ledSignal On  input ");
      Serial.print(temp);
      generatePin(temp, ON);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();

      Serial.print("2ledSignal Off input ");
      Serial.print(temp);
      generatePin(temp, OFF);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();
    }
    Serial.println();
    for (i = 1; i <= signal3LedCount; i++) {
      temp = i + signal3LedStartAddress;
      Serial.print("3ledSignal On  input ");
      Serial.print(temp);
      generatePin(temp, ON);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();

      Serial.print("3ledSignal Off input ");
      Serial.print(temp);
      generatePin(temp, OFF);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();
    }
    Serial.println();

    i = 0;
    for (i = 1; i <= turnoutServoCount; i++) {
      temp = turnoutServoSartAddress + i;
      Serial.print("Servo Turnout THROW input ");
      Serial.print(temp);
      generatePin(temp, THROW);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();

      Serial.print("Servo Turnout CLOSE input ");
      Serial.print(temp);
      generatePin(temp, CLOSE);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();
    }
    Serial.println();
    i = 0;
    for (i = 1; i <= turnoutSnapCount; i++) {
      temp = turnoutSnapSartAddress + i;
      Serial.print("SNAP Turnout THROW ");
      Serial.print(temp);
      generatePin(temp, THROW);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();
      Serial.print("SNAP Turnout CLOSE ");
      Serial.print(temp);
      generatePin(temp, CLOSE);
      Serial.print(" board No  ");
      Serial.print(boardSlot.boardNo);
      Serial.print(" board Pin ");
      Serial.print(boardSlot.boardPin);
      Serial.print(" process  ");
      Serial.print( boardSlot.processed);
      Serial.println();
    }
    exectuion = true;
  }
}

void generatePin(long input, String val) {
  if (input <= lightStartAddress + lightCount) {
    pinNo = (input - lightStartAddress);
    return findBoardPin(pinNo);

  } else if (input <= signal2LedStartAddress + signal2LedCount) {
    pinNo = (input - signal2LedStartAddress) + lightCount;
    return findBoardPin(pinNo);

  } else if (input <= signal3LedStartAddress + signal3LedCount) {
    pinNo = (input - signal3LedStartAddress) + lightCount + signal2LedCount;
    return findBoardPin(pinNo);

  } else if (input <= turnoutServoSartAddress + turnoutServoCount) {
    pinNo = (input - turnoutServoSartAddress);
    pinNo =  pinNo + (totalLightBoard * 16 );
    return findBoardPin(pinNo);
  } else if (input <= turnoutSnapSartAddress + turnoutSnapCount) {
    pinNo = ((input - turnoutSnapSartAddress) * 2);
    if (pinNo % 2 == 0 && val == CLOSE) {
      pinNo = pinNo + ((totalLightBoard + totalTunroutServoBoard) * 16 );
      return findBoardPin(pinNo);
    } else {
      pinNo = pinNo - 1;
      pinNo = pinNo + ((totalLightBoard + totalTunroutServoBoard) * 16 );
      return findBoardPin(pinNo);
    }
  } else {
    boardSlot.processed = false;
    boardSlot.boardNo = -1;
    boardSlot.boardPin = -1;
    return boardSlot;
  }
}

void findBoardPin(int pinNo) {
  Serial.print(" requestedAddress  ");
  Serial.print( pinNo);
  Serial.print("  ");

  pinNo = pinNo - 1;
  int board = (pinNo / 16);
  if (board <= _totalBoards && pinNo <= (_totalBoards * 16)) {
    int totalPins = (board * 16);
    int pin = (pinNo - totalPins);
    pin = (pin == -1) ? 0 : pin;
    boardSlot.processed = true;
    boardSlot.boardNo = board;
    boardSlot.boardPin = pin;
    return boardSlot;
  }
  boardSlot.processed = false;
  return boardSlot;
}
