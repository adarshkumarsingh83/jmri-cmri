
#include <Wire.h>
#include <CMRI.h>
#include <Auto485.h>
#include <Adafruit_PWMServoDriver.h>

#define DE_PIN 2
#define CMRI_ADDR 1
#define PCA_PINS 16
#define PCA_BOARD_COUNT 3
#define SERVO_NO 48 // 16 1st board with address (0,15) + 16 2nd board with address (16,31) + 16 3rd board with address (32,47)  

Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus);

// set the pca boards objects with address here
Adafruit_PWMServoDriver pwms[] = {Adafruit_PWMServoDriver(0x40), Adafruit_PWMServoDriver(0x41), Adafruit_PWMServoDriver(0x42)};

int i = 0;
int servoStatus[SERVO_NO]; //Create a table to hold the status of each turnout, signal, etc.
int turnThrow[SERVO_NO]; //Create a table to hold the throw value for each servo
int turnClose[SERVO_NO]; //Create a table to hold the close value for each servo

/*
  //approach option
  int servoStatus[SERVO_NO];
  int turnThrow[] = {x1, x2....xn};
  int turnClose[] = {x1, x2....xn};
*/

void setup() {

  bus.begin(9600);

  for (i = 0; i < PCA_BOARD_COUNT; i++) {
    pwms[i].begin();
    pwms[i].setPWMFreq(50);
  }

  /*
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
}

void loop() {

  cmri.process();

  for (i = 0; i < PCA_PINS; i++) {
    // for board 0 servo 0 to 15
    boardOperation(pwms[0], i, i);
    // for board 1 servo 16 to 31
    boardOperation(pwms[1], i, i + 16);
    // for board 2 servo 31 to 47
    boardOperation(pwms[2], i, i + 32);
    // for board 3 servo 48 to 64
    //boardOperation(pwms[3],i,i+48);
  }

}

void boardOperation(Adafruit_PWMServoDriver pwm, int  boardIndex, int board) {
  servoStatus[board] = cmri.get_bit(board);
  if (servoStatus[board] == 1) {
    pwm.writeMicroseconds(boardIndex, turnThrow[board]);
  } else {
    pwm.writeMicroseconds(boardIndex, turnClose[board]);
  }
}
