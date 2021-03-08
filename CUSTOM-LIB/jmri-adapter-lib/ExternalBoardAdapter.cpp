/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#include <Arduino.h>
#include "ExternalBoardAdapter.h"


void ExternalBoardAdapter::initAdapter() {
  pca9685Board = &Pca9685Board(_signalCount + _lightCount);
}

void ExternalBoardAdapter::setSignal( int signalCount) {
  _signalCount = signalCount;
}
void ExternalBoardAdapter::setTurnout( int turnoutCount) {
  _turnoutCount = turnoutCount;
}
void ExternalBoardAdapter::setLight(int lightCount) {
  _lightCount = lightCount;
}

void ExternalBoardAdapter::processRequest(char type, int jmriAddress, bool value) {
  if (type == 'S') {
    processSignalRequest(jmriAddress, value);
  } else if (type == 'T') {
    processTurnoutRequest( jmriAddress, value);
  } else if (type == 'L') {
    processLightRequest(jmriAddress, value);
  }
}

void ExternalBoardAdapter::processSignalRequest(int pin, bool signalValue) {
  if (signalValue) {
    //pcf8574Board->switchOn(pin);
  } else {
    //pcf8574Board->switchOff(pin);
  }
}

void ExternalBoardAdapter::processLightRequest(int pin, bool signalValue) {
  if (signalValue) {
    //pcf8574Board->switchOn(pin);
  } else {
    //pcf8574Board->switchOff(pin);
  }
}

void ExternalBoardAdapter::processTurnoutRequest(int pin, bool throwValue) {
  if (throwValue) {
    pca9685Board->throwSwitch(pin);
  } else {
    pca9685Board->closeSwitch(pin);
  }
}
