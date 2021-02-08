#include <CMRI.h>
#include<Auto485.h>

#define DE_PIN 2
#define CMRI_ADDR 1
#define OPEN_PIN 12
#define CLOSE_PIN 13

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

int cmriInput = -1;

enum SWITCH_STATES {
  STRAIGHT,
  TURN,
  OFF
};
SWITCH_STATES switchState = OFF;

void setup() {
  bus.begin(9600);
  pinMode(OPEN_PIN, OUTPUT);
  pinMode(CLOSE_PIN, OUTPUT);
}


void loop() {

  cmri.process();
  cmriInput = cmri.get_bit(0);
  delay(200);
  switch (switchState) {
    case STRAIGHT:
      switchStraightOn();
      break;
    case TURN:
      switchTurnOn();
      break;
    case OFF:
      switchOff();
      break;
  }
}

void switchOff() {
  if (cmriInput == 1) {
    switchState = STRAIGHT;
  } else if (cmriInput == 0) {
    switchState = TURN;
  } else {
    digitalWrite(OPEN_PIN, LOW);
    digitalWrite(CLOSE_PIN, LOW);
    switchState = OFF;
  }
}

void switchTurnOn() {
  digitalWrite(OPEN_PIN, HIGH);
  digitalWrite(CLOSE_PIN, LOW);
  delay(200);
  switchState = OFF;
}


void switchStraightOn() {
  digitalWrite(OPEN_PIN, LOW);
  digitalWrite(CLOSE_PIN, HIGH);
  delay(200);
  switchState = OFF;
}
