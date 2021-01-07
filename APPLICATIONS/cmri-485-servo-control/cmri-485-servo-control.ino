#include <CMRI.h>
#include <Auto485.h>
#include <Servo.h>

#define CMRI_ADDR 1
#define DE_PIN 2 

int turnout1 = 0;

Auto485 bus(DE_PIN); // Arduino pin 2 -> MAX485 DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs
Servo turnOut1;

void setup() {
    turnOut1.attach(2);
    turnOut1.write(0);
    bus.begin(9600);
}

void loop() {
    cmri.process();
    turnout1 = (cmri.get_bit(0));
    if (turnout1 == 1){
        turnOut1.write(90);
    } else {
        turnOut1.write(0);
    }
}
