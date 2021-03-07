/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#ifndef CmriJmriAdapter_h
#define CmriJmriAdapter_h

#include <Arduino.h>
#include <CMRI.h>
#include "ExternalBoardAdapter.h"


class CmriJmriAdapter {


  private:

    int _jmriSignalStartAddress;
    int _signalCount;
    int _jmriTurnoutStartAddress;
    int _turnoutCount;
    int _jmriLightStartAddress;
    int _lightCount;
    CMRI * _cmri;
    ExternalBoardAdapter externalBoardAdapter();

    char findTypeByJmriAddress(int  jmriAddress);

  public:

    CmriJmriAdapter(CMRI * cmri) {
      _cmri = cmri;
      _jmriSignalStartAddress = -1;
      _signalCount = -1;
      _jmriTurnoutStartAddress = -1;
      _turnoutCount = -1;
      _jmriLightStartAddress = -1;
      _lightCount = -1;
    }

    void initCmriJmriAdapter();

    void activateCmriSignal(int jmriSignalStartAddress, int signalCount);

    void activateCmriTurnout(int jmriTurnoutStartAddress, int turnoutCount) ;

    void activateCmriLight(int lightStartAddress, int lightCount);

    void processJmri();

    ~CmriJmriAdapter() {
    }
};

#endif
