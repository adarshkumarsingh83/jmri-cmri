
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/

#include <CMRI.h>
#include<Auto485.h>
#include "CmriJmriAdapter.h"

#define DE_PIN 2
#define CMRI_ADDR 1

// arduino pin 2 for DE and RE pins
Auto485 bus(DE_PIN);

// defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs
CMRI cmri(CMRI_ADDR, 24, 48, bus);

CmriJmriAdapter cmriJmriAdapter = CmriJmriAdapter(&cmri);

void setup() {
  bus.begin(9600);
  cmriJmriAdapter.activateCmriSignal(1001, 10);
  cmriJmriAdapter.activateCmriTurnout(1101, 10);
  cmriJmriAdapter.activateCmriLight(1201, 10);
  cmriJmriAdapter.initCmriJmriAdapter();
}


void loop() {
  cmriJmriAdapter.processJmri();
  delay(500);
}
