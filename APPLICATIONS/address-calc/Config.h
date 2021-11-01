/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h

#include <Arduino.h>


struct BoardPin {
  int boardNo;
  int boardPin;
  bool processed;
};

#define ON "ON"
#define OFF "OF"
#define THROW "TH"
#define CLOSE "CL"

#define DELEY_TIME 10000
#define MESSAGE_BROAD_RATE 9600

#define  lightStartAddress 10000         //  LIGHT STARTING ADDRESS
#define  lightCount 2                    //  LIGHT COUNT

#define  signal2LedStartAddress 20000    //  2LED SIGNAL STARTING ADDRESS
#define  signal2LedCount 10              //  2LED SIGNAL COUNT

#define  signal3LedStartAddress 30000    //  3LED SIGNAL STARTING ADDRESS
#define  signal3LedCount 30              //  3LED SIGNAL COUNT

#define turnoutServoSartAddress 40000   //  SERVO TURNOUT STARTING ADDRESS
#define turnoutServoCount 8             //  SERVO TURNOUT COUNT

#define  turnoutSnapSartAddress 50000    //  SNAP TURNOUT STARTING ADDRESS
#define  turnoutSnapCount 3

#define  totalLightBoard 3
#define  totalTunroutServoBoard 1
#define  totalTunroutSnapBoard 1
const int  _totalBoards = totalLightBoard + totalTunroutServoBoard + totalTunroutSnapBoard;
#endif
