/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#ifndef Pca9685_h
#define Pca9685_h

#include <Arduino.h>
#include "Adafruit_PWMServoDriver.h"


class Pca9685 {

  private:
    int _totalPins = 16;
    int _boardsAddress;
    int _pwmFrequency;

    bool * _pca9685PinStateList;
    Adafruit_PWMServoDriver _pwm;

    void init();

  public:

    Pca9685() {
      init();
    }
    void initPca9685();
    void setBoardAddress(int boardsAddress);
    void setPwmFrequency(int pwmFrequency);
    bool switchOnPca9685Pin(int pinNo);
    bool switchOffPca9685Pin(int pinNo);
    void refreshPin(int pinNo, bool state);
    void refreshPca9685Board();
    void resetPca9685Board();
    void displayPca9685();

    ~Pca9685() {
      delete [] _pca9685PinStateList;
    }
};
#endif
