
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#include "Pca9685.h"
#include "Config.h"


void Pca9685::initPca9685(char type) {
  //_pwm = Adafruit_PWMServoDriver(_boardsAddress);
  // _pwm.begin();
  _type = type;
  if (_type == 'L') {
    // _pwm.setPWMFreq(PWM_LIGHT_FREQUENCY);
    for (int i = 0; i < TOTAL_BOARD_PIN; i++) {
      _pca9685PinStateList[i] = false;
    }
  } else if (_type == 'T') {
    // _pwm.setPWMFreq(PWM_TURNOUT_FREQUENCY);
    _pca9685PinList = new Pca9685Pin[TOTAL_BOARD_PIN];
    for (int i = 0; i < TOTAL_BOARD_PIN; i++) {
      _pca9685PinList[i]._openState = 1000;
      _pca9685PinList[i]._closeState = 2000;
      _pca9685PinList[i]._isOpen = false;
    }
  }
}

bool Pca9685::setSwitchOpenCloseRange(int pinNo, int openRange, int closeRange) {
  if (_type == 'T') {
    _pca9685PinList[pinNo]._openState = openRange;
    _pca9685PinList[pinNo]._closeState = closeRange;
    return true;
  } else {
    return false;
  }
}

void Pca9685::setPwmFrequency(int pwmFrequency) {
  this->_pwmFrequency = pwmFrequency;
  // _pwm.setPWMFreq(_pwmFrequency);
}

void Pca9685::setBoardAddress(int boardsAddress) {
  this->_boardsAddress = boardsAddress;
}

void Pca9685::turnoutThrow(int pinNo) {
  if (_type == T) {
    _pca9685PinList[pinNo]._isOpen = true;
    //_pwm.writeMicroseconds(i, _pca9685PinList[pinNo]._openState );
    Serial.println(" TURNOUT THROW");
  }
}

void Pca9685::turnoutClose(int pinNo) {
  if (_type ==  T) {
    _pca9685PinList[pinNo]._isOpen = false;
    //_pwm.writeMicroseconds(i, _pca9685PinList[pinNo]._closeState );
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
