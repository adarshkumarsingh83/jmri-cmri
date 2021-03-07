/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#ifndef ExternalBoardAdapter_h
#define ExternalBoardAdaptert_h

#include "Pcf8574.h"
#include "Pcf8574Board.h"
#include "Pca9685.h"
#include "Pca9685Board.h"

class ExternalBoardAdapter {

  private:
     Pca9685Board *pca9685Board;
     Pcf8574Board *pcf8574Board;
    
  public:
    ExternalBoardAdapter() {
    }
    
    void processSignalRequest(int pin, bool signalValue);
    void processLightRequest(int pin, bool signalValue);
    void processTurnoutRequest(int pin, bool  throwValue);

    ~ExternalBoardAdapter() {
    }
};

#endif
