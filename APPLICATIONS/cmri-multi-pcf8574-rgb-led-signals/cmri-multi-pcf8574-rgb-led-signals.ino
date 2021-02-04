#include <CMRI.h>
#include<Auto485.h>
#include <Wire.h>

#define DE_PIN 2
#define CMRI_ADDR 1

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

// Max 8 board can be chain into this starting fromn 0x20 to 0x27 which will give 64 extra output pin 
int boardAddress [] = {0x20, 0x21 };         // PCF8574 board1 - 0x20,   board2  - 0x21 ... board8 0x27 
int boardsCount = sizeof(boardAddress) / sizeof(int);    // calculating counts of the boards
int LED_Pattern_ON = 0x00;  // LED Sequence Start pattern, one LED on .   =>  0b0000000000000000
int LED_Pattern_OFF = 0xFFFF;  // LED Sequence Start pattern, one LED off =>  0b1111111111111111

void setup() {
  bus.begin(9600);

  // configure the intrupt pin
  pinMode(3, INPUT_PULLUP);

  Wire.begin();

  for (int i = 0; i < boardsCount; i++) {
    // Turn off all GPIO pins on both I2C expanders by writing all "1"
    Wire.beginTransmission(boardAddress[i]);
    Wire.write(0xFF);
    Wire.endTransmission();
  }
}

void loop() {
  cmri.process();
  
  int   pinInc = 0;
  int sum = 0;

  for (int i = 0; i < boardsCount; i++) {
    lightOperations(sum, boardAddress[i], pinInc);
    pinInc += 8;
    sum = 0;
  }
}

void lightOperations(int sum , int boardAddress, int boardNo) {

  int position = cmri.get_bit(7 + boardNo);
  if (position == 1) {
    sum += 128;
  }

  position = cmri.get_bit(6 + boardNo);
  if (position == 1) {
    sum += 64;
  }

  position = cmri.get_bit(5 + boardNo);
  if (position == 1) {
    sum += 32;
  }

  position = cmri.get_bit(4 + boardNo);
  if (position == 1) {
    sum += 16;
  }

  position = cmri.get_bit(3 + boardNo);
  if (position == 1) {
    sum += 8;
  }

  position = cmri.get_bit(2 + boardNo);
  if (position == 1) {
    sum += 4;
  }

  position = cmri.get_bit(1 + boardNo);
  if (position == 1) {
    sum += 2;
  }

  position = cmri.get_bit(0 + boardNo);
  if (position == 1) {
    sum += 1;
  }

  Wire.beginTransmission(boardAddress);
  Wire.write(sum);
  Wire.endTransmission();
}
