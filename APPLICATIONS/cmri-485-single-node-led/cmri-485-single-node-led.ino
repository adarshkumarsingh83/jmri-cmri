#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 7
#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 24, 48, bus); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

void setup() {
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  bus.begin(9600);
}

void loop() {

  cmri.process();

  // 2: update output. Reads bit 0 of T packet and sets the LED to this
  digitalWrite(RED_LED_PIN, cmri.get_bit(0));

  digitalWrite(GREEN_LED_PIN, cmri.get_bit(7));

}
