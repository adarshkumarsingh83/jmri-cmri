#include <CMRI.h>
#include <Auto485.h>

#define DE_PIN 2
#define CMRI_ADDR 1
#define ON LOW
#define OFF HIGH
#define DELAY_VALUE 300

enum SIGNAL_STATES {
  UNOCCUPIED,
  OCCUPYING_FROM_START_OF_BLOCK,
  OCCUPYING_FROM_END_OF_BLOCK,
  OCCUPIED,
};

// total no of sensor count
const int SENSOR_COUNT = 3;
SIGNAL_STATES sensorsState[SENSOR_COUNT] = {UNOCCUPIED, UNOCCUPIED, UNOCCUPIED};
SIGNAL_STATES stateCurrent = UNOCCUPIED;
SIGNAL_STATES statePrevious = UNOCCUPIED;
// const bool ENABLE_CONSOLE = false;


int r;
int c;
int blockSensorVal[SENSOR_COUNT][2];
/*
    todo add the number of pins for {startblockpin,endblockpin}
    max we can add 5 block which is 10 pins together
*/
int blockSensor[SENSOR_COUNT][2] = {{3, 4}, {5, 6}, {7, 8}};


Auto485 bus(DE_PIN);
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {

  bus.begin(9600);

  /*
    if (ENABLE_CONSOLE) {
      Serial.begin(9600);
    }
  */

  for (r = 0; r < SENSOR_COUNT; r++) {
    for (c = 0; c < 2; c++) {
      pinMode(blockSensor[r][c], INPUT);
    }
  }
}


void loop() {

  cmri.process();

  for (r = 0; r < SENSOR_COUNT; r++) {
    for (c = 0; c < 2; c++) {
      blockSensorVal[r][c] = digitalRead(blockSensor[r][c]);
    }
  }

  delay(DELAY_VALUE);

  for (r = 0 ; r < SENSOR_COUNT; r++) {
    statePrevious = sensorsState[r];
    switch (statePrevious) {
      case UNOCCUPIED:
        stateCurrent =  unOccupiedBlock(statePrevious, blockSensorVal[r][0], blockSensorVal[r][1]);
        if (stateCurrent != statePrevious) {
          setCmriSingals(r, stateCurrent);
          sensorsState[r] = stateCurrent;
        }
        //displayData(r, "unOccupiedBlock", blockSensorVal[r][0], blockSensorVal[r][1]);
        break;
      case OCCUPYING_FROM_START_OF_BLOCK:
        stateCurrent = occupiedFromEndOfBlock(statePrevious, blockSensorVal[r][0], blockSensorVal[r][1]);
        if (stateCurrent != statePrevious) {
          setCmriSingals(r, stateCurrent);
          sensorsState[r] = stateCurrent;
        }
        // displayData(r, "occupiedFromEndOfBlock", blockSensorVal[r][0], blockSensorVal[r][1]);
        break;
      case OCCUPYING_FROM_END_OF_BLOCK:
        stateCurrent = occupiedFromStartOfBlock(statePrevious, blockSensorVal[r][0], blockSensorVal[r][1]);
        if (stateCurrent != statePrevious) {
          setCmriSingals(r, stateCurrent);
          sensorsState[r] = stateCurrent;
        }
        // displayData(r, "occupiedFromStartOfBlock", blockSensorVal[r][0], blockSensorVal[r][1]);
        break;
      case OCCUPIED:
        stateCurrent = occupiedBlock(statePrevious, blockSensorVal[r][0], blockSensorVal[r][1]);
        if (stateCurrent != statePrevious) {
          setCmriSingals(r, stateCurrent);
          sensorsState[r] = stateCurrent;
        }
        // displayData(r, "occupiedBlock", blockSensorVal[r][0], blockSensorVal[r][1]);
        break;
    }
  }
}


void setCmriSingals(int sensorNo, SIGNAL_STATES signalState) {
  if (signalState == UNOCCUPIED) {
    // setting sensor 0 with 0 in-active
    cmri.set_bit(sensorNo, 0);
  } else {
    // setting sensor 0 with 1 active
    cmri.set_bit(sensorNo, 1);
  }
}


SIGNAL_STATES unOccupiedBlock(SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == ON  && endSensor == OFF) {
    signalState = OCCUPYING_FROM_START_OF_BLOCK;// block is occupied entered from sens1
  } else if (startSensor == OFF  && endSensor == ON) {
    signalState = OCCUPYING_FROM_END_OF_BLOCK;// block is occupied entered from sens2
  }
  return signalState;
}


SIGNAL_STATES occupiedFromEndOfBlock(SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == OFF && endSensor == ON) {
    signalState = OCCUPIED;
  }
  return signalState;
}


SIGNAL_STATES occupiedFromStartOfBlock(SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == ON  && endSensor == OFF) {
    signalState = OCCUPIED;
  }
  return signalState;
}


SIGNAL_STATES occupiedBlock(SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if ((startSensor == OFF) && (endSensor == OFF)) {
    signalState = UNOCCUPIED;
  }
  return signalState;
}

/*
  void displayData(int sensorNo, String message, int startSensor, int endSensor) {
  if (ENABLE_CONSOLE) {
    Serial.print(sensorNo);
    Serial.println("  " + message);
    Serial.print(startSensor);
    Serial.print(" ");
    Serial.println(endSensor);
    Serial.println();
  }
  }
*/
