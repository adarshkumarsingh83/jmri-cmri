 #include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

// defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs
CMRI cmri(CMRI_ADDR, 24, 48, bus); 

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);  
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(47));

  cmri.set_bit(0, !digitalRead(SENSOR_1));
  cmri.set_bit(23, !digitalRead(SENSOR_2));
}
