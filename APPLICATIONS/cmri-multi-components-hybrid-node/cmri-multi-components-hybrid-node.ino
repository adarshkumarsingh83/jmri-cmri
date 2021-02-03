
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <CMRI.h>
#include <Auto485.h>


#define DE_PIN 2
#define CMRI_ADDR 1
#define numServos 48 // 16 1st board with address (0,15) + 16 2nd board with address (16,31) + 16 3rd board with address (32,47)  

#define IR_SENSOR_PIN_3  3
#define IR_SENSOR_PIN_4  4
#define IR_SENSOR_PIN_5  5


#define LED_LIGHT_PIN_13  13

Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x40);//setup the board 0
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDriver(0x41);//setup the board 1
Adafruit_PWMServoDriver pwm3 = Adafruit_PWMServoDriver(0x42);//setup the board 2

Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus);


int Status[numServos]; //Create a table to hold the status of each turnout, signal, etc.
int Throw[numServos]; //Create a table to hold the throw value for each servo
int Close[numServos]; //Create a table to hold the close value for each servo

void setup() {

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
  Throw[0] = 1015;
  Close[0] = 1800;


  //Servo connection 0 - point motor
  //board 1 address 0 servo will 16 then 17, 18 and so on till 31
  Throw[16] = 1015;
  Close[16] = 1800;

  //Servo connection 0 - point motor
  //board 2 address 0 servo will be 32 then 33 and so on till 47
  Throw[32] = 1015;
  Close[32] = 1800;

   // for IR input sensors pins 
   pinMode(IR_SENSOR_PIN_3, INPUT_PULLUP); 
   pinMode(IR_SENSOR_PIN_4, INPUT_PULLUP); 
   pinMode(IR_SENSOR_PIN_5, INPUT_PULLUP); 


   pinMode(LED_LIGHT_PIN_13, OUTPUT);
}

void loop() {

  cmri.process();


  for (int i = 0; i < 16; i++) {

    // for board 0 servo 0 to 15
    Status[i] = (cmri.get_bit(i));
    if (Status[i] == 1) {
      pwm1.writeMicroseconds(i, Throw[i]);
    } else {
      pwm1.writeMicroseconds(i, Close[i]);
    }

     
    // for board 1 servo 16 to 31
    int board1 = 16 + i;
    Status[board1] = (cmri.get_bit(board1));
    if (Status[board1] == 1) {
      pwm2.writeMicroseconds(i, Throw[board1]);
    } else {
      pwm2.writeMicroseconds(i, Close[board1]);
    }

    
    // for board 2 servo 31 to 47
    int board2 = 32 + i;
    Status[board2] = (cmri.get_bit(board2));
    if (Status[board2] == 1) {
      pwm3.writeMicroseconds(i, Throw[board2]);
    } else {
      pwm3.writeMicroseconds(i, Close[board2]);
    }


     // Do not read 0, 1, 2, 13
      cmri.set_bit(0, !digitalRead(IR_SENSOR_PIN_3));  //Bit 0 = address 1001 in JMRI
      cmri.set_bit(1, !digitalRead(IR_SENSOR_PIN_4));  //Bit 1 = address 1002 in JMRI
      cmri.set_bit(2, !digitalRead(IR_SENSOR_PIN_5));  //Bit 2 = address 1003 in JMRI


      // LED LIGHT 
      //digitalWrite(LED_LIGHT_PIN_13, cmri.get_bit(0));
  }

}
