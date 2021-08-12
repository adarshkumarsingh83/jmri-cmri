
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include "Pca9685.h"
#include "Config.h"


void Pca9685::initPca9685(char type) {
  //_pwm = Adafruit_PWMServoDriver(_boardsAddress);
  // _pwm.begin();
  // _pwm.setPWMFreq(_pwmFrequency);
  _type = type;
  for (int i = 0; i < TOTAL_BOARD_PIN; i++) {
    _pca9685PinStateList[i] = false;
  }
}

void Pca9685::setPwmFrequency(int pwmFrequency) {
  this->_pwmFrequency = pwmFrequency;
}

void Pca9685::setBoardAddress(int boardsAddress) {
  this->_boardsAddress = boardsAddress;
}

void Pca9685::turnoutThrow(int pinNo) {
  if (_type == T) {
    _pca9685PinStateList[pinNo] = true;
    _pca9685PinStateList[pinNo + 1] = false;
    //  _pwm.setPWM(pinNo, 4096, 0);
    delay(200);
    //  _pwm.setPWM(pinNo, 0, 4096);
    Serial.println(" TURNOUT THROW");
  }
}

void Pca9685::turnoutClose(int pinNo) {
  if (_type ==  T) {
    _pca9685PinStateList[pinNo] = true;
    _pca9685PinStateList[pinNo - 1] = false;
    // _pwm.setPWM(pinNo, 4096, 0);
    delay(200);
    // _pwm.setPWM(pinNo, 0, 4096);
    Serial.println(" TURNOUT CLOSE\n");
  }
}

void Pca9685::ledOn(int pinNo) {
  if (_type == L) {
    _pca9685PinStateList[pinNo] = true;
    // _pwm.setPWM(pinNo, 4096, 0);
    Serial.println(" LED ON");
  }
}
void Pca9685::ledOff(int pinNo) {
  if (_type == L) {
    _pca9685PinStateList[pinNo] = false;
    // _pwm.setPWM(pinNo, 0, 4096);
   Serial.println(" LED OFF \n");   
  }
}

char Pca9685::getType() {
  return _type;
}
