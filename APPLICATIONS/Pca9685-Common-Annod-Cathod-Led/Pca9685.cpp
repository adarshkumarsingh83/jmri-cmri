/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include <Arduino.h>
#include "Pca9685.h"



void Pca9685::init() {
  _pca9685PinStateList = new bool[_totalPins];
  _pwmFrequency = 1000;
  for (int i = 0; i < _totalPins; i++) {
    _pca9685PinStateList[i] = false;
  }
}

void Pca9685::initPca9685() {
  _pwm = Adafruit_PWMServoDriver(_boardsAddress);
  _pwm.begin();
  _pwm.setPWMFreq(_pwmFrequency);
}

void Pca9685::setPwmFrequency(int pwmFrequency) {
  this->_pwmFrequency = pwmFrequency;
}

void Pca9685::setBoardAddress(int boardsAddress) {
  this->_boardsAddress = boardsAddress;
}


bool Pca9685::switchOnPca9685Pin(int pinNo) {
  _pca9685PinStateList[pinNo] = true;
  refreshPin(pinNo, true);
  Serial.println("switchOnPca9685Pin");
  return true;
}

bool Pca9685::switchOffPca9685Pin(int pinNo) {
  _pca9685PinStateList[pinNo] = false;
  refreshPin(pinNo, false);
  Serial.println("switchOffPca9685Pin");
  return true;
}

void Pca9685::resetPca9685Board() {
  for (int i = 0; i < _totalPins; i++) {
    _pca9685PinStateList[i] = false;
  }
  refreshPca9685Board();
}

void Pca9685::refreshPca9685Board() {
  for (int i = 0; i < _totalPins; i++) {
    bool state = _pca9685PinStateList[i];
    if (state) {
      _pwm.setPWM(i, 4096, 0);
    } else {
      _pwm.setPWM(i, 0, 4096);
    }
  }
}

void Pca9685::refreshPin(int pinNo, bool state) {
  if (state) {
    _pwm.setPWM(pinNo, 4096, 0);
  } else {
    _pwm.setPWM(pinNo, 0, 4096);
  }
}



void Pca9685::displayPca9685() {
  Serial.print("Board No ");
  Serial.print(_boardsAddress);
  Serial.print(" total pins ");
  Serial.println(this->_totalPins);
  for (int i = 0; i < _totalPins; i++) {
    bool state = _pca9685PinStateList[i];
    Serial.println();
    Serial.print(" Pin ");
    Serial.print(i);
    Serial.print(" PinState ");
    Serial.println(((state) ? "ON" : "OFF"));
  }
}
