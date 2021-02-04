#include <CMRI.h>
#include<Auto485.h>
#include <Wire.h>

#define DE_PIN 2
#define CMRI_ADDR 1

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

int address = 0x20;          // PCF8574 device 1
int LED_Pattern_ON = 0x00;  // LED Sequence Start pattern, one LED on .   =>  0b0000000000000000
int LED_Pattern_OFF = 0xFFFF;  // LED Sequence Start pattern, one LED off =>  0b1111111111111111

int sum = 0;
int position = 0;
void setup() {

  bus.begin(9600);

  Wire.begin();
  // Turn off all GPIO pins on both I2C expanders by writing all "1"
  Wire.beginTransmission(address);
  Wire.write(0xFF);
  Wire.endTransmission();
  pinMode(3, INPUT_PULLUP);
}

/*
  address is configured for red then green
  then same cycle red then green till the pins ends
  in one pcf8574 we can configure 4 rgb led for red yellow and green signal
*/
void loop() {

  cmri.process();
  sum = 0;

  position = cmri.get_bit(7);
  if (position == 1) {
    sum += 128;
  }

  position = cmri.get_bit(6);
  if (position == 1) {
    sum += 64;
  }


  position = cmri.get_bit(5);
  if (position == 1) {
    sum += 32;
  }
  position = cmri.get_bit(4);
  if (position == 1) {
    sum += 16;
  }


  position = cmri.get_bit(3);
  if (position == 1) {
    sum += 8;
  }
  position = cmri.get_bit(2);
  if (position == 1) {
    sum += 4;
  }


  position = cmri.get_bit(1);
  if (position == 1) {
    sum += 2;
  }
  position = cmri.get_bit(0);
  if (position == 1) {
    sum += 1;
  }

  Wire.beginTransmission(address);
  Wire.write(sum);
  Wire.endTransmission();
}
