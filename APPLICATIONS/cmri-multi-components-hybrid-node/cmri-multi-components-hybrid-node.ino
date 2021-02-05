#include <Wire.h>
#include <CMRI.h>
#include <Auto485.h>
#include <Adafruit_PWMServoDriver.h>

#define DE_PIN 2
#define CMRI_ADDR 1
#define PCA_PINS 16
#define PCA_BOARD_COUNT 2
#define SERVO_NO 32 // 16 1st board with address (0,15) + 16 2nd board with address (16,31) + 16 3rd board with address (32,47)  

#define IR_SENSOR_PIN_3  3
#define IR_SENSOR_PIN_4  4
#define IR_SENSOR_PIN_5  5

Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus);
// set the pca boards objects with address here
Adafruit_PWMServoDriver pwms[] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41), Adafruit_PWMServoDriver(0x42)};

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

int sum = 0;
int pinInc = 0;
int position = 0;
int boardAddress [] = {0x20, 0x21 };         // PCF8574 board1 - 0x20,   board2  - 0x21 ... board8 0x27
int boardsCount = sizeof(boardAddress) / sizeof(int);    // calculating counts of the boards
int LED_Pattern_ON = 0x00;  // LED Sequence Start pattern, one LED on .   =>  0b0000000000000000
int LED_Pattern_OFF = 0xFFFF;  // LED Sequence Start pattern, one LED off =>  0b1111111111111111


void setup() {

  bus.begin(9600);
  // configure the intrupt pin
  pinMode(3, INPUT_PULLUP);


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


  // for IR input sensors pins
  pinMode(IR_SENSOR_PIN_3, INPUT_PULLUP);
  pinMode(IR_SENSOR_PIN_4, INPUT_PULLUP);
  pinMode(IR_SENSOR_PIN_5, INPUT_PULLUP);

  for (i = 0; i < boardsCount; i++) {
    // Turn off all GPIO pins on both I2C expanders by writing all "1"
    Wire.beginTransmission(boardAddress[i]);
    Wire.write(0xFF);
    Wire.endTransmission();
  }
}

void loop() {

  cmri.process();

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


  //SENSOR PINS OPERATIONS
  cmri.set_bit(0, !digitalRead(IR_SENSOR_PIN_3));  //Bit 0 = address 1001 in JMRI
  cmri.set_bit(1, !digitalRead(IR_SENSOR_PIN_4));  //Bit 1 = address 1002 in JMRI
  cmri.set_bit(2, !digitalRead(IR_SENSOR_PIN_5));  //Bit 2 = address 1003 in JMRI

  pinInc = 32;
  sum = 0;
  for (i = 0; i < boardsCount; i++) {
    lightOperations(sum, boardAddress[i], pinInc);
    pinInc += 8;
    sum = 0;
  }
}


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
