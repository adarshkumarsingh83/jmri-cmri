#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <CMRI.h>
#include <Auto485.h>

#define CMRI_ADDR 1
#define DE_PIN 2

#define numServos 48 // 16 1st board with address (0,15) + 16 2nd board with address (16,31) + 16 3rd board with address (32,47)  

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);//setup the board 0
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);//setup the board 1
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);//setup the board 2

Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus);


int Status[numServos]; //Create a table to hold the status of each turnout, signal, etc.
int Throw[numServos]; //Create a table to hold the throw value for each servo
int Close[numServos]; //Create a table to hold the close value for each servo

void setup() {

  Serial.begin(9600);
  bus.begin(9600);
  pwm1.begin();
  pwm1.setPWMFreq(60);

  pwm2.begin();
  pwm2.setPWMFreq(60);

  pwm3.begin();
  pwm3.setPWMFreq(60);


  //SET THE THROW AND CLOSE VALUES FOR EACH SERVO BASED ON THE CALIBRATION PROCESS

  //Servo connection 0 - point motor
  //board 0 address 0 servo will be 0 then 1,2,3 and so on till 15
  Throw[0] = 100;
  Close[0] = 200;


  //Servo connection 0 - point motor
  //board 1 address 0 servo will 16 then 17, 18 and so on till 31
  Throw[16] = 100;
  Close[16] = 200;


  //Servo connection 0 - point motor
  //board 2 address 0 servo will be 32 then 33 and so on till 47
  Throw[32] = 100;
  Close[32] = 200;


  //Servo connection 0 - point motor
  //board 3 address 0 servo will be 48 then 49, 50 and so on till 63
  // Throw[48] = 100;
  // Close[48] = 200;

}

void loop() {

  cmri.process();


  for (int i = 0; i < numServos; i++) {


    // for board 0 servo 0 to 15
    Status[i] = (cmri.get_bit(i));
    if (Status[i] == 1) {
      pwm.writeMicroseconds(i, Throw[i]);
    } else {
      pwm.writeMicroseconds(i, Close[i]);
    }


    // for board 1 servo 16 to 31
    Status[i + 16] = (cmri.get_bit(i + 16));
    if (Status[i + 16] == 1) {
      pwm.writeMicroseconds(i, Throw[i + 16]);
    } else {
      pwm.writeMicroseconds(i, Close[i + 16]);
    }


    // for board 2 servo 31 to 47
    Status[i + 32] = (cmri.get_bit(i + 32));
    if (Status[i + 32] == 1) {
      pwm.writeMicroseconds(i, Throw[i + 32]);
    } else {
      pwm.writeMicroseconds(i, Close[i + 32]);
    }

    /*
      // for board 3 servo 48 to 64
      Status[i + 48] = (cmri.get_bit(i + 48));
      if (Status[i + 48] == 1) {
      pwm.writeMicroseconds(i, Throw[i + 48]);
      } else {
      pwm.writeMicroseconds(i, Close[i + 48]);
      }
    */

  }

}
