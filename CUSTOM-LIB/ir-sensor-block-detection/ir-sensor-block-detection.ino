
#include "BlockSensors.h"
#define NO_OF_BLOCKS 3

BlockSensors *blockSensors;

void setup() {
  Serial.begin(9600);
  BlockSensors  object = BlockSensors(NO_OF_BLOCKS);
  blockSensors = &object;
  blockSensors->setBlockSensorPins(0, 11, 12);
  blockSensors->setBlockSensorPins(1, 13, 14);
  blockSensors->setBlockSensorPins(2, 15, 16);
  blockSensors->initBlockSensors();
}

void loop() {
  delay(1000);
  for (int i = 0; i < NO_OF_BLOCKS; i++) {
    bool isBlockOccuipied = blockSensors->isSensorBlockOccupied(i);
    Serial.print("Block no  ");
    Serial.print(i);
    Serial.print("  isBlockOccuipied  ");
    Serial.println(isBlockOccuipied);
  }
}
