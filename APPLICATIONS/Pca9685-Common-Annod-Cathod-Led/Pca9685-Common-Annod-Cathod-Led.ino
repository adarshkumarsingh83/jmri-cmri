#include "Pca9685.h"
#include "Pca9685Board.h"
#include "Config.h"



int MAX_PINS = 0;

Pca9685Board pca9685Board;
void setup() {
  Serial.begin(BROAD_RATE);
  pca9685Board.initPca9685Boards(NO_OF_BOARDS);
  MAX_PINS = NO_OF_BOARDS * 3;
}

void loop() {
  delay(1000);

  int pinNo = random(0, MAX_PINS);
  Serial.print("MAX PIN ");
  Serial.println(MAX_PINS);
  Serial.print("PIN NO ");
  Serial.println(pinNo);
  pca9685Board.switchOn(pinNo);
  pca9685Board.displayPinState();
  delay(1000);
  pca9685Board.switchOff(pinNo);
  pca9685Board.displayPinState();
  delay(1000);

}
