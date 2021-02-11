#include <CMRI.h>
#include <Auto485.h>

#define DE_PIN 2
#define CMRI_ADDR 1
#define ON LOW
#define OFF HIGH
#define DELAY_VALUE 300

int r;
int c;
int startSignal;
int endSignal;
const int SENSOR_COUNT = 3;
int blockSignalSensorVal[SENSOR_COUNT][2];
int blockSignalSensor[SENSOR_COUNT][2] = {{3, 4}, {5, 6}, {7, 8}};

bool ENABLE_CONSOLE = false;

enum SIGNAL_STATES {
  ST_G1_G2,
  ST_R1_R2_1,
  ST_R1_R2_2,
  ST_R1_R2_3,
};
SIGNAL_STATES sensorsSignalState[SENSOR_COUNT] = {ST_G1_G2, ST_G1_G2, ST_G1_G2};
SIGNAL_STATES signalStateCurrent = ST_G1_G2;
SIGNAL_STATES signalStatePrevious = ST_G1_G2;

Auto485 bus(DE_PIN);
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {

  bus.begin(9600);

  if (ENABLE_CONSOLE) {
    Serial.begin(9600);
  }

  for (r = 0; r < SENSOR_COUNT; r++) {
    for (c = 0; c < 2; c++) {
      pinMode(blockSignalSensor[r][c], INPUT);
    }
  }
}

void loop() {

  cmri.process();

  for (r = 0; r < SENSOR_COUNT; r++) {
    for (c = 0; c < 2; c++) {
      blockSignalSensorVal[r][c] = digitalRead(blockSignalSensor[r][c]);
    }
  }

  delay(DELAY_VALUE);

  for (r = 0 ; r < SENSOR_COUNT; r++) {
    signalStatePrevious = sensorsSignalState[r];
    switch (signalStatePrevious) {
      case ST_G1_G2:
        signalStateCurrent =  signal_G1_G2(r, signalStatePrevious, blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        if (signalStateCurrent != signalStatePrevious) {
          setCmriSingals(r, signalStateCurrent);
          sensorsSignalState[r] = signalStateCurrent;
        }
        displayData(r, "signal_G1_G2", blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        break;
      case ST_R1_R2_1:
        signalStateCurrent = signal1_R1_R2(r, signalStatePrevious, blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        if (signalStateCurrent != signalStatePrevious) {
          setCmriSingals(r, signalStateCurrent);
          sensorsSignalState[r] = signalStateCurrent;
        }
        displayData(r, "signal1_R1_R2", blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        break;
      case ST_R1_R2_2:
        signalStateCurrent = signal2_R1_R2(r, signalStatePrevious, blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        if (signalStateCurrent != signalStatePrevious) {
          setCmriSingals(r, signalStateCurrent);
          sensorsSignalState[r] = signalStateCurrent;
        }
        displayData(r, "signal2_R1_R2", blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        break;
      case ST_R1_R2_3:
        signalStateCurrent = signal3_R1_R2(r, signalStatePrevious, blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        if (signalStateCurrent != signalStatePrevious) {
          setCmriSingals(r, signalStateCurrent);
          sensorsSignalState[r] = signalStateCurrent;
        }
        displayData(r, "signal3_R1_R2", blockSignalSensorVal[r][0], blockSignalSensorVal[r][1]);
        break;
    }
  }
}
void setCmriSingals(int sensorNo, SIGNAL_STATES signalState) {
  if (signalState == ST_G1_G2) {
    // setting sensor 0 with 0 in-active
    cmri.set_bit(sensorNo, 0);
  } else {
    // setting sensor 0 with 1 active
    cmri.set_bit(sensorNo, 1);
  }
}

SIGNAL_STATES signal_G1_G2(int sensorNo, SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == ON  && endSensor == OFF) {
    signalState = ST_R1_R2_1;// block is occupied entered from sens1
  } else if (startSensor == OFF  && endSensor == ON) {
    signalState = ST_R1_R2_2;// block is occupied entered from sens2
  }
  return signalState;
}


SIGNAL_STATES signal1_R1_R2(int sensorNo, SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == OFF && endSensor == ON) {
    signalState = ST_R1_R2_3; //switched to transition Red signal state
  }
  return signalState;
}

SIGNAL_STATES signal2_R1_R2(int sensorNo, SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if (startSensor == ON  && endSensor == OFF) {
    signalState = ST_R1_R2_3; //switched to transition Red signal state
  }
  return signalState;
}


SIGNAL_STATES signal3_R1_R2(int sensorNo, SIGNAL_STATES signalState, int startSensor, int endSensor) {

  if ((startSensor == OFF) && (endSensor == OFF)) {
    signalState = ST_G1_G2; //switched to Green unoccupied signal
  }
  return signalState;
}

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
