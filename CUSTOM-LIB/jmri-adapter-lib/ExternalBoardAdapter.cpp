/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#include <Arduino.h>
#include "ExternalBoardAdapter.h"

void ExternalBoardAdapter::processSignalRequest(int jmriAddress, bool signalValue) {
  if (signalValue) {
    //pcf8574Board.switchOn(jmriAddress);
  } else {
    //pcf8574Board.switchOff(jmriAddress);
  }
}

void ExternalBoardAdapter::processLightRequest(int jmriAddress, bool signalValue) {
  if (signalValue) {
    //pcf8574Board.switchOn(jmriAddress);
  } else {
    //pcf8574Board.switchOff(jmriAddress);
  }
}

void ExternalBoardAdapter::processTurnoutRequest(int jmriAddress, bool  throwValue) {

}
