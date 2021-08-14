
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/


#include <Arduino.h>
#include "Pca9685BoardManager.h"


void Pca9685BoardManager::initPca9685Boards() {

  if ((NO_OF_TURNOUT_BOARDS + NO_OF_LIGHT_BOARDS) > 0 && (NO_OF_TURNOUT_BOARDS + NO_OF_LIGHT_BOARDS) < 65) {

    Serial.print("Total Pca9685 boards for Turnout and Light ");
    Serial.println(NO_OF_TOTAL_BOARDS);

    if (NO_OF_TURNOUT_BOARDS > -1 && NO_OF_TURNOUT_BOARDS < 65) {
      Serial.print("Total Pca9685 boards for Turnout ");
      Serial.println(NO_OF_TURNOUT_BOARDS);
    } else {
      Serial.println("invalid arguments supplied ");
      return;
    }

    if (NO_OF_LIGHT_BOARDS > -1 && NO_OF_LIGHT_BOARDS < 65) {
      Serial.print("Total Pca9685 boards for Light ");
      Serial.println(NO_OF_LIGHT_BOARDS);
    } else {
      Serial.println("invalid arguments supplied ");
      return;
    }

    _pca9685Boards = new Pca9685[NO_OF_TOTAL_BOARDS];
    int i = 0;
    if (NO_OF_TOTAL_BOARDS > 0 && NO_OF_TURNOUT_BOARDS != 0) {
      for (i = 0; i <  NO_OF_TURNOUT_BOARDS; i++) {
        _pca9685Boards[i].setBoardAddress(_boardAddress[i]);
        _pca9685Boards[i].setPwmFrequency(_pwmFrequency);
        _pca9685Boards[i].initPca9685(T);
      }
    }
    if (NO_OF_TOTAL_BOARDS > 0 && NO_OF_LIGHT_BOARDS != 0) {
      for ( ; i < NO_OF_TOTAL_BOARDS; i++) {
        _pca9685Boards[i].setBoardAddress(_boardAddress[i]);
        _pca9685Boards[i].setPwmFrequency(_pwmFrequency);
        _pca9685Boards[i].initPca9685(L);
      }
    }
  } else {
    Serial.println("invalid arguments supplied ");
  }

}

bool Pca9685BoardManager::switchThrow(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == T) {
    _pca9685Boards[boardId].turnoutThrow(pinId);
    return true;
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchClose(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == T) {
    _pca9685Boards[boardId].turnoutClose(pinId);
    return true;
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchOn(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == L) {
    _pca9685Boards[boardId].ledOn(pinId);
    return true;
  } else {
    return false;
  }
}

bool Pca9685BoardManager::switchOff(int boardId, int pinId) {
  if (_pca9685Boards[boardId].getType() == L) {
    _pca9685Boards[boardId].ledOff(pinId);
    return true;
  } else {
    return false;
  }
}
