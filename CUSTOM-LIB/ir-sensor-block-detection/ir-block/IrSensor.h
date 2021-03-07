/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshkumarsingh83@gmail.com
*/
#ifndef IrSensor_h
#define IrSensor_h

enum SIGNAL_STATES {
  UNOCCUPIED,
  OCCUPYING_FROM_START_OF_BLOCK,
  OCCUPYING_FROM_END_OF_BLOCK,
  OCCUPIED,
};

class IrSensor {

  private:

    int _startBlockSensorPin;
    int _endBlockSensorPin;
    int _startBlockSensorVal;
    int _endBlockSensorVal;

    SIGNAL_STATES _stateCurrent = UNOCCUPIED;
    SIGNAL_STATES _statePrevious = UNOCCUPIED;

    void init();
    void calculateBlockOccupancy();

    SIGNAL_STATES unOccupiedBlock(SIGNAL_STATES signalState, int startSensor, int endSensor);
    SIGNAL_STATES occupiedFromEndOfBlock(SIGNAL_STATES signalState, int startSensor, int endSensor);
    SIGNAL_STATES occupiedFromStartOfBlock(SIGNAL_STATES signalState, int startSensor, int endSensor);
    SIGNAL_STATES occupiedBlock(SIGNAL_STATES signalState, int startSensor, int endSensor) ;

  public:

    IrSensor() {
      void init();
    }

    IrSensor(int startBlockSensorPin, int endBlockSensorPin): _startBlockSensorPin(startBlockSensorPin), _endBlockSensorPin(endBlockSensorPin) {
      void init();
    }
    
    void setStartAndEndBlockSensorPin(int startBlockSensorPin, int endBlockSensorPin);
    
    bool isBlockOccupied();

    ~IrSensor() {
    }

};

#endif
