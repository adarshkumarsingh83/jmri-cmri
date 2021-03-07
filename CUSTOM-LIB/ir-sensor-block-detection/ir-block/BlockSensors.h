/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#ifndef BlockSensors_h
#define BlockSensors_h

#include "IrSensor.h"

class BlockSensors {

  private:
    int _totalSensor;
    IrSensor * _irSensorBlocks;

  public:
    BlockSensors(int totalSensor): _totalSensor(totalSensor) {
    }

    void initBlockSensors();
    void setBlockSensorPins(int blockNo, int startBlockSensorPin, int endBlockSensorPin);
    bool isSensorBlockOccupied(int blockNo);

    ~BlockSensors() {
      for (int i = 0; i < _totalSensor; i++) {
        delete &_irSensorBlocks[i];
      }
      delete[] _irSensorBlocks;
    }
};

#endif
