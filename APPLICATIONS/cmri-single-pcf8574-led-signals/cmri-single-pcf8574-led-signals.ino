
#include <CMRI.h>
#include<Auto485.h>
#include <Wire.h>

#define DE_PIN 2
#define CMRI_ADDR 1

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins
CMRI cmri(CMRI_ADDR, 24, 48, bus); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

int addr1 = 0x20;          // PCF8574 device 1
int LED_Pattern_ON = 0x00;  // LED Sequence Start pattern, one LED on .   =>  0b0000000000000000
int LED_Pattern_OFF = 0xFFFF;  // LED Sequence Start pattern, one LED off =>  0b1111111111111111
void setup() {
  
  bus.begin(9600);
  Serial.begin(9600);
  Wire.begin();
  // Turn off all GPIO pins on both I2C expanders by writing all "1"
  Wire.beginTransmission(addr1);
  Wire.write(0xFF);
  Wire.endTransmission();
  pinMode(3, INPUT_PULLUP);
}

void loop() {

  cmri.process();
  int sum = 0;
  int position0 = cmri.get_bit(7);
  Serial.println(position0);
  if (position0 == 0) {
    sum += 128;
  }
  int position1 = cmri.get_bit(6);
   Serial.println(position1);
  if (position1 == 0) {
    sum += 64;
  }
  int position2 = cmri.get_bit(5);
  if (position2 == 0) {
    sum += 32;
  }
  int position3 = cmri.get_bit(4);
  if (position3 == 0) {
    sum += 16;
  }
  int position4 = cmri.get_bit(3);
  if (position4 == 0) {
    sum += 8;
  }
  int position5 = cmri.get_bit(2);
  if (position5 == 0) {
    sum += 4;
  }
  int position6 = cmri.get_bit(1);
  if (position6 == 0) {
    sum += 2;
  }
  int position7 = cmri.get_bit(0);
  if (position7 == 0) {
    sum += 1;
  }

  // Send the LSB 8 bits of LED_Pattern out to device 1
  Wire.beginTransmission(addr1);
  Wire.write(sum);
  Wire.endTransmission();
}
