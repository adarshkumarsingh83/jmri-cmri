/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include "./CmriJmriAdapter.h"

void CmriJmriAdapter::initCmriJmriAdapter() {

}

void CmriJmriAdapter::activateCmriSignal(int jmriSignalStartAddress, int signalCount) {
  _jmriSignalStartAddress = jmriSignalStartAddress;
  _signalCount = signalCount;
}

void CmriJmriAdapter::activateCmriTurnout(int jmriTurnoutStartAddress, int turnoutCount) {
  _jmriTurnoutStartAddress = jmriTurnoutStartAddress;
  _turnoutCount = turnoutCount;
}

void CmriJmriAdapter::activateCmriLight(int lightStartAddress, int lightCount) {
  _jmriLightStartAddress = lightStartAddress;
  _lightCount = lightCount;
}


void CmriJmriAdapter::processJmri() {
  _cmri->process();

  if (_signalCount != -1 ) {
    int totalJmriSignalAddress = _jmriSignalStartAddress + _signalCount;
    for (int i = _jmriSignalStartAddress; i < totalJmriSignalAddress; i++) {
      //todo conect to the respective implemenation
      _cmri->get_bit(i);
    }
  }

  if (_turnoutCount != -1) {
    int totalJmriTurnoutAddress = _jmriTurnoutStartAddress + _turnoutCount;
    for (int i = _jmriTurnoutStartAddress; i < totalJmriTurnoutAddress; i++) {
      //todo conect to the respective implemenation
      _cmri->get_bit(i);
    }
  }

  if (_lightCount != -1) {
    int totalJmriLightAddress = _jmriLightStartAddress + _lightCount;
    for (int i = _jmriLightStartAddress; i < totalJmriLightAddress; i++) {
      //todo conect to the respective implemenation
      _cmri->get_bit(i);
    }
  }
}
