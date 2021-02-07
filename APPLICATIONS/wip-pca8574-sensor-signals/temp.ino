#include <Wire.h>
#include <CMRI.h>
#include<Auto485.h>

#define DE_PIN 2
#define CMRI_ADDR 1
#define ARDUINO_INT_PIN 3

// arduino pin 2 for DE and RE pins
Auto485 bus(DE_PIN);
// defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs
CMRI cmri(CMRI_ADDR, 24, 48, bus);

// PCF8574 device 1
const int address = 0x20;
// LED Sequence Start pattern, one LED on .   =>  0b0000000000000000
const int LED_Pattern_ON = 0x00;
// LED Sequence Start pattern, one LED off =>  0b1111111111111111
const int LED_Pattern_OFF = 0xFFFF;


int sum = 0;
int input = -1;
int position = 0;
int dataOnPin = -1;
bool irActive = false;

void infraRedActive();

void setup() {
  Serial.begin(9600);
  bus.begin(9600);
  Wire.begin();
  Wire.beginTransmission(address);
  Wire.write(0xFF);
  Wire.endTransmission();
  pinMode(ARDUINO_INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ARDUINO_INT_PIN), infraRedActive, CHANGE);
}

void loop() {
  sum = 0;
  cmri.process();

  if (irActive == true) {
    input = readInput(address, 7);
    if (input & 0b10000000) {
      cmri.set_bit(0, 1);
    } else {
      cmri.set_bit(0, 0);
    }
    irActive = false;
  }

  sum += 128;
  position = cmri.get_bit(6);
  if (position == 0) {
    sum += 64;
  }
  position = cmri.get_bit(5);
  if (position == 0) {
    sum += 32;
  }
  position = cmri.get_bit(4);
  if (position == 0) {
    sum += 16;
  }
  position = cmri.get_bit(3);
  if (position == 0) {
    sum += 8;
  }
  position = cmri.get_bit(2);
  if (position == 0) {
    sum += 4;
  }
  position = cmri.get_bit(1);
  if (position == 0) {
    sum += 2;
  }
  position = cmri.get_bit(0);
  if (position == 0) {
    sum += 1;
  }

  Wire.beginTransmission(address);
  Wire.write(sum);
  Wire.endTransmission();
}

byte readInput(int address, int pin) {
  dataOnPin = -1;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, pin );
  if (Wire.available()) {
    dataOnPin = Wire.read();
  }
  Wire.endTransmission();
  return dataOnPin;
}

void infraRedActive() {
  irActive = true;
}
