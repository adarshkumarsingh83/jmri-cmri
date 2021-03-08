/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#ifndef ExternalBoardAdapter_h
#define ExternalBoardAdaptert_h

#include "Pcf8574Board.h"
#include "Pca9685Board.h"

class ExternalBoardAdapter {

  private:
    int _signalCount;
    int _turnoutCount;
    int _lightCount;

    Pca9685Board *pca9685Board;
    Pcf8574Board *pcf8574Board;

    void processSignalRequest(int pin, bool signalValue);
    void processLightRequest(int pin, bool signalValue);
    void processTurnoutRequest(int pin, bool  throwValue);

  public:
    ExternalBoardAdapter() {
    }

    void initAdapter();
    void setSignal( int signalCount);
    void setTurnout( int turnoutCount);
    void setLight(int lightCount);
    void processRequest(char type, int pin, bool signalValue);

    ~ExternalBoardAdapter() {
    }
};

#endif
