#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <CMRI.h>
#include <Auto485.h>

#define CMRI_ADDR 1
#define DE_PIN 2
#define SERVO_COUNT 2



Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //setup the board address 0
Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus);

int i = 0;
int servoBits[SERVO_COUNT];
// appraoch option 
//int turnThrow[SERVO_COUNT]; //Create a table to hold the throw value for each servo
//int turnClose[SERVO_COUNT]; //Create a table to hold the close value for each servo
// define the turn throw points 0   1    2  ...... n
int turnThrow[SERVO_COUNT] = {100, 100};
int turnClose[SERVO_COUNT] = {200, 200};

void setup() {

  bus.begin(9600);

  pwm.begin();
  pwm.setPWMFreq(60);  // This is the maximum PWM frequency

  /*
   // appraoch option 
    SET THE THROW AND CLOSE VALUES FOR EACH SERVO BASED ON TURN HEAD ON SERVO
    OR SET INDIVIDUALLY TO THE ARRAY OF THE turnThrow[]={X1,X2,X3....Xn} & turnClose[]={X1,X2,X3....Xn}
    board 0 address 0 servo will be 0 then 1,2,3 and so on till 15
    board 1 address 0 servo will 16 then 17, 18 and so on till 31
    board 2 address 0 servo will be 32 then 33 and so on till 47
    board 3 address 0 servo will be 48 then 49, 50 and so on till 63

    for (i = 0; i < SERVO_COUNT; i++) {
      turnThrow[i] = 100;
      turnClose[i] = 200;
    }
  */
}

void loop() {

  cmri.process();

  for (i = 0; i < SERVO_COUNT; i++) {
    servoBits[i] = cmri.get_bit(i);
  }

  for (i = 0; i < SERVO_COUNT; i++) {
    if (servoBits[i] == 1) {
      pwm.setPWM(i, 0, turnThrow[i] );
    }
    if (servoBits[i] == 0) {
      pwm.setPWM(i, 0, turnClose[i]);
    }
  }
}
