#include <CMRI.h>
#include <Auto485.h>

#define CMRI_ADDR 6

#define LED 13

#define DE_PIN 2

Auto485 bus(DE_PIN); 

CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {
     pinMode(LED, OUTPUT);
     bus.begin(9600);
}

void loop() {

     cmri.process();
     digitalWrite(LED, cmri.get_bit(0));

}
