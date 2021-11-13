/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include "Pca9685Board.h"
#include "Config.h"

void Pca9685Board::initPca9685Boards(int totalPca9685Boards) {
  if (totalPca9685Boards > 0 && totalPca9685Boards < 65) {
    _totalPca9685Boards = totalPca9685Boards;
  } else {
    _totalPca9685Boards = 0;
  }
  _pca9685Boards = new Pca9685[_totalPca9685Boards];
  for (int i = 0; i < _totalPca9685Boards; i++) {
    _pca9685Boards[i].setBoardAddress(_boardAddress[i]);
    _pca9685Boards[i].setPwmFrequency(_pwmFrequency);
    _pca9685Boards[i].initPca9685();
  }
}

void Pca9685Board::setFrequency(int pwmFrequency) {
  if (pwmFrequency > 39 && pwmFrequency < 1001) {
    _pwmFrequency = pwmFrequency;
  } else {
    _pwmFrequency = 1000;
  }
}

Pca9685Board::BoardPin Pca9685Board::findBoardPin(int pinNo) {
  Pca9685Board::BoardPin boardSlot;
  pinNo = pinNo - 1;
  int board = (pinNo / 16);
  if (board <= _totalPca9685Boards && pinNo <= (_totalPca9685Boards * 16)) {
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

bool Pca9685Board::switchOn(int pinNo) {
  Pca9685Board::BoardPin boardSlot = findBoardPin(pinNo);
  if (enableAnode) {
    _pca9685Boards[boardSlot.boardNo].switchOffPca9685Pin(boardSlot.boardPin);
  } else {
    _pca9685Boards[boardSlot.boardNo].switchOnPca9685Pin(boardSlot.boardPin);
  }
  return true;
}

bool Pca9685Board::switchOff(int pinNo) {
  Pca9685Board::BoardPin boardSlot = findBoardPin(pinNo);
  if (enableAnode) {
    _pca9685Boards[boardSlot.boardNo].switchOnPca9685Pin(boardSlot.boardPin);
  } else {
    _pca9685Boards[boardSlot.boardNo].switchOffPca9685Pin(boardSlot.boardPin);
  }
  return true;
}

void Pca9685Board::restBoard(int boardNo) {
  _pca9685Boards[boardNo].resetPca9685Board();
}

void Pca9685Board::refreshBoard(int boardNo) {
  _pca9685Boards[boardNo].refreshPca9685Board();
}

void Pca9685Board::displayPinState() {
  Serial.print("Total Boards ");
  Serial.println(_totalPca9685Boards);
  for (int i = 0; i < _totalPca9685Boards; i++) {
    _pca9685Boards[i].displayPca9685();
    Serial.println("-");
  }
}
