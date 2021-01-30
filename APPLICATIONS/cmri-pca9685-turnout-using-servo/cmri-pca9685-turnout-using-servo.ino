#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <CMRI.h>
#include <Auto485.h>

#define CMRI_ADDR 1
#define DE_PIN 2 
int Tbit[2];

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(); //setup the board address 0
Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus); 


void setup() {
  Serial.begin(9600);
  bus.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(60);  // This is the maximum PWM frequency
  //pwm.setPWM(0, 0, 150);
  //pwm.setPWM(1, 0, 200);
 
}

void loop(){
   cmri.process();
   Tbit[0] = (cmri.get_bit(0)); //TMU1
   Tbit[1] = (cmri.get_bit(1)); //TBD1
   
   if (Tbit[0] == 1){
     pwm.setPWM(0, 0, 100);
     Serial.println("trow");
   }
   if (Tbit[0] == 0){
     pwm.setPWM(0, 0, 200);
     Serial.println("close");
   }
   if (Tbit[1] == 1){
     pwm.setPWM(1, 0, 100);
   }
   if (Tbit[1] == 0){
     pwm.setPWM(1, 0, 200);
   }
}
