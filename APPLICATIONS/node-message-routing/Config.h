

/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h

#include <Arduino.h>

#define DELEY_TIME 10000
#define MESSAGE_BROAD_RATE 9600


/*
    JMRI ADDRESS 0  -> 499   SNAP SWITCHES  => 499
    JMRI ADDRESS 500  -> 999   SERVO SWITCHES => 499
    JMRI ADDRESS 1000 -> 1499  2LED SIGNALS   => 499
    JMRI ADDRESS 1500 -> 1999  3LED SIGNALS   => 499
    JMRI ADDRESS 2000 -> 2048  LIGHTS         => 48
*/

#define SNAP_SWITCHES_MIN 0
#define SNAP_SWITCHES_MAX 499

#define SERVO_SWITCHES_MIN 500
#define SERVO_SWITCHES_MAX 999

#define SIGNALS_2LED_MIN 1000
#define SIGNALS_2LED_MAX 1499

#define SIGNALS_3LED_MIN 1500
#define SIGNALS_3LED_MAX 1999

#define LIGHTS_MIN 2000
#define LIGHTS_MAX 2048

struct Node {
  const int nodeNo;
  const int lightStartAddress;         //  LIGHT STARTING ADDRESS
  const int lightCount;                //  LIGHT COUNT
  const int signal2LedStartAddress;    //  2LED SIGNAL STARTING ADDRESS
  const int signal2LedCount;           //  2LED SIGNAL COUNT
  const int signal3LedStartAddress;    //  3LED SIGNAL STARTING ADDRESS
  const int signal3LedCount;           //  3LED SIGNAL COUNT
  const int turnoutServoSartAddress;   //  SERVO TURNOUT STARTING ADDRESS
  const int turnoutServoCount;         //  SERVO TURNOUT COUNT
  const int turnoutSnapSartAddress;    //  SNAP TURNOUT STARTING ADDRESS
  const int turnoutSnapCount;          //  SNAP TURNOUT COUNT
};

#define NODE_COUNT 5

const Node nodes[NODE_COUNT] = {
  {
    .nodeNo = 1,
    .lightStartAddress = 2000,
    .lightCount = 7,
    .signal2LedStartAddress = 1000,
    .signal2LedCount = 13,
    .signal3LedStartAddress = 1500,
    .signal3LedCount = 27,
    .turnoutServoSartAddress = 500,
    .turnoutServoCount = 3,
    .turnoutSnapSartAddress = 0,
    .turnoutSnapCount = 21
  },
  {
    .nodeNo = 2,
    .lightStartAddress = 2100,
    .lightCount = 3,
    .signal2LedStartAddress = 1100,
    .signal2LedCount = 27,
    .signal3LedStartAddress = 1600,
    .signal3LedCount = 30,
    .turnoutServoSartAddress = 600,
    .turnoutServoCount = 29,
    .turnoutSnapSartAddress = 100,
    .turnoutSnapCount = 13,
  },
  {
    .nodeNo = 3,
    .lightStartAddress = 2200,
    .lightCount = 5,
    .signal2LedStartAddress = 1300,
    .signal2LedCount = 19,
    .signal3LedStartAddress = 1700,
    .signal3LedCount = 23,
    .turnoutServoSartAddress = 700,
    .turnoutServoCount = 32,
    .turnoutSnapSartAddress = 200,
    .turnoutSnapCount = 17,
  },
  {
    .nodeNo = 4,
    .lightStartAddress = 2300,
    .lightCount = 5,
    .signal2LedStartAddress = 1400,
    .signal2LedCount = 19,
    .signal3LedStartAddress = 1800,
    .signal3LedCount = 23,
    .turnoutServoSartAddress = 800,
    .turnoutServoCount = 32,
    .turnoutSnapSartAddress = 300,
    .turnoutSnapCount = 17,
  },
  {
    .nodeNo = 5,
    .lightStartAddress = 2400,
    .lightCount = 5,
    .signal2LedStartAddress = 1500,
    .signal2LedCount = 19,
    .signal3LedStartAddress = 1900,
    .signal3LedCount = 23,
    .turnoutServoSartAddress = 900,
    .turnoutServoCount = 32,
    .turnoutSnapSartAddress = 400,
    .turnoutSnapCount = 17,
  }
};

#endif
