
#include <CMRI.h>
#include <Auto485.h>

#define CMRI_ADDR 1
#define DE_PIN 2
#define RED_PIN 13
#define IR_SENSOR_PIN  3

Auto485 bus(DE_PIN);
// defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {
  bus.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() {
  cmri.process();
  if (digitalRead(IR_SENSOR_PIN) == LOW) {
    digitalWrite(RED_PIN, HIGH);
    cmri.set_bit(0, 1);
    delay(100);
  } else {
    digitalWrite(RED_PIN, LOW);
    cmri.set_bit(0, 0);
    delay(100);
  }
}
