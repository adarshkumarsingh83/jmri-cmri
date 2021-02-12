/*
   FOR UNO BELOW CONFIGURATION IS MAX
  5 sensors  1001 starting address in jmri to 1024
   eg=> 1001 1002 1003 
  32 servos  1001 starting address in jmri to 1032
  eg=> 1001 10017 
  16 combine (red yellow green) signal lights or lights 10033 starting address in jmri to 1048 
  eg=> 1033 1034 1035 - 1011 1012 1013 

  FOR MEGA BELOW CONFIGURAITON IS MAX
  ~ sensors  1001 starting address in jmri to ~
  ~ servos  1001 starting address in jmri to ~
  ~ combine (red yellow green) signal lights or lights 10033 starting address in jmri to ~
*/

#include <CMRI.h>
#include <Auto485.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define DE_PIN 2
#define CMRI_ADDR 1

// sensors constants
#define ON LOW
#define OFF HIGH

//servo constants
#define PCA_PINS 16
#define PCA_BOARD_COUNT 2
#define SERVO_NO 32 // 16 1st board with address (0,15) + 16 2nd board with address (16,31) + 16 3rd board with address (32,47)  


#define DELAY_VALUE 200

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



int i = 0;
int servoStatus[SERVO_NO]; //Create a table to hold the status of each turnout, signal, etc.
int turnThrow[SERVO_NO]; //Create a table to hold the throw value for each servo
int turnClose[SERVO_NO]; //Create a table to hold the close value for each servo

/*
  //turn out angle diclration approach option
  int servoStatus[SERVO_NO];
  int turnThrow[] = {x1, x2....xn};
  int turnClose[] = {x1, x2....xn};
*/

// signals constans and diclaration
int sum = 0;
int pinInc = 0;
int position = 0;
int boardAddress [] = {0x20, 0x21 };         // PCF8574 board1 - 0x20,   board2  - 0x21 ... board8 0x27
int boardsCount = sizeof(boardAddress) / sizeof(int);    // calculating counts of the boards
const int LED_Pattern_ON = 0x00;  // LED Sequence Start pattern, one LED on .   =>  0b0000000000000000
const int LED_Pattern_OFF = 0xFFFF;  // LED Sequence Start pattern, one LED off =>  0b1111111111111111


Auto485 bus(DE_PIN);
CMRI cmri(CMRI_ADDR, 24, 48, bus);

// set the pca boards objects with address here
Adafruit_PWMServoDriver pwms[] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41)};

void setup() {

  bus.begin(9600);

  /*
    if (ENABLE_CONSOLE) {
      Serial.begin(9600);
    }
  */
  // for sensors
  for (r = 0; r < SENSOR_COUNT; r++) {
    for (c = 0; c < 2; c++) {
      pinMode(blockSensor[r][c], INPUT);
    }
  }

  // for servos
  for (i = 0; i < PCA_BOARD_COUNT; i++) {
    pwms[i].begin();
    pwms[i].setPWMFreq(50);
  }

  /*
    //if approach option is uncommeted comment below init code.
    SET THE THROW AND CLOSE VALUES FOR EACH SERVO BASED ON TURN HEAD ON SERVO
    OR SET INDIVIDUALLY TO THE ARRAY OF THE turnThrow[]={X1,X2,X3....Xn} & turnClose[]={X1,X2,X3....Xn}
    board 0 address 0 servo will be 0 then 1,2,3 and so on till 15
    board 1 address 0 servo will 16 then 17, 18 and so on till 31
    board 2 address 0 servo will be 32 then 33 and so on till 47
    board 3 address 0 servo will be 48 then 49, 50 and so on till 63
  */
  for (i = 0; i < SERVO_NO; i++) {
    turnThrow[i] = 1100;
    turnClose[i] = 1500;
  }


  // for signals
  for (i = 0; i < boardsCount; i++) {
    // Turn off all GPIO pins on both I2C expanders by writing all "1"
    Wire.beginTransmission(boardAddress[i]);
    Wire.write(0xFF);
    Wire.endTransmission();
  }
}


void loop() {

  cmri.process();

  // for readingg sensors data
  for (r = 0; r < SENSOR_COUNT; r++) {
    for (c = 0; c < 2; c++) {
      blockSensorVal[r][c] = digitalRead(blockSensor[r][c]);
    }
  }

  //delay(DELAY_VALUE);
  sensorsOperation();

  // for readingg sensors data
  for (i = 0; i < PCA_PINS; i++) {
    // for board 0 servo 0 to 15
    servoOperation(pwms[0], i, i);
    // for board 1 servo 16 to 31
    servoOperation(pwms[1], i, i + 16);
    // for board 2 servo 31 to 47
    // servoOperation(pwms[2], i, i + 32);
    // for board 3 servo 48 to 64
    //servoOperation(pwms[3],i,i+48);
  }

  // for the signals lights
  pinInc = 32;
  sum = 0;
  for (i = 0; i < boardsCount; i++) {
    lightOperations(sum, boardAddress[i], pinInc);
    pinInc += 8;
    sum = 0;
  }
}



void sensorsOperation() {
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


void servoOperation(Adafruit_PWMServoDriver pwm, int  boardIndex, int board) {
  servoStatus[board] = cmri.get_bit(board);
  if (servoStatus[board] == 1) {
    pwm.writeMicroseconds(boardIndex, turnThrow[board]);
  } else {
    pwm.writeMicroseconds(boardIndex, turnClose[board]);
  }
}


void lightOperations(int sum , int boardAddress, int boardNo) {

  position = cmri.get_bit(7 + boardNo);
  if (position == 0) {
    sum += 128;
  }

  position = cmri.get_bit(6 + boardNo);
  if (position == 0) {
    sum += 64;
  }

  position = cmri.get_bit(5 + boardNo);
  if (position == 0) {
    sum += 32;
  }

  position = cmri.get_bit(4 + boardNo);
  if (position == 0) {
    sum += 16;
  }

  position = cmri.get_bit(3 + boardNo);
  if (position == 0) {
    sum += 8;
  }

  position = cmri.get_bit(2 + boardNo);
  if (position == 0) {
    sum += 4;
  }

  position = cmri.get_bit(1 + boardNo);
  if (position == 0) {
    sum += 2;
  }

  position = cmri.get_bit(0 + boardNo);
  if (position == 0) {
    sum += 1;
  }

  // Send the LSB 8 bits of LED_Pattern out to device 1
  Wire.beginTransmission(boardAddress);
  Wire.write(sum);
  Wire.endTransmission();
}
