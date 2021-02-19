#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 32, 96, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 64 inputs, 64 outputs

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(95));
}
