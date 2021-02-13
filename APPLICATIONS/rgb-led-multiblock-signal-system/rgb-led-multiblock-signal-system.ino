
#define BLOCK_STARTING_SENSOR_PIN A0 //Sensor is setup on pin A0
#define BLOCK_ENDING_SENSOR_PIN A1 //Sensor is setup on pin A1

#define BLOCK_START_G1_LED 2 // Green Signal 1 is digital pin 2
#define BLOCK_START_R1_LED 3// Red Signal 1 is digital pin 3
#define BLOCK_END_G2_LED 4// Green Signal 2 is digital pin 4
#define BLOCK_END_R2_LED 5 //Red Signal 2 is digital pin 5

#define BLOCK_OCCUPIED_SIGNAL_PIN 6 // The transmit pin for the previous and next block in the sequence
#define PRIVIOUS_BLOCK_REC_SIGNAL_PIN A2// The recieve pin for the previous block in the sequence
#define NEXT_BLOCK_REC_SIGNAL_PIN A3// The recieve pin for the next block in the sequence

#define OFF LOW
#define ON  HIGH
#define DELAY_VALUE 200
#define SENSOR_COMP_VALUE 500
#define BLOCK_SIGNAL_REC_VALUE 300
#define BLOCK_SIGNAL_SEND_VALUE 1023

// to enable and display the console data print
const bool displayOn = true;

int blockStartingSensorVal = -1;
int blockEndingSensorVal = -1;
int prevBlockOccupiedSignalVal = -1;
int nxtBlockOccupiedSignalVal  = -1;


enum SIGNAL_STATES {
  CURRENT_UNOCCUPIED_BLOCK,
  CURRENT_UNOCCUPIED_NEXT_OCCUPIED,
  CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED,
  CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED,
  OCCUPYING_FROM_START,
  OCCUPYING_FROM_END,
  OCCUPIED_BLOCK,
};

SIGNAL_STATES signalState = CURRENT_UNOCCUPIED_BLOCK;

void setup() {
  Serial.begin(9600);

  //Establish all of our pins at inputs or outputs
  pinMode(BLOCK_STARTING_SENSOR_PIN, INPUT);
  pinMode(BLOCK_ENDING_SENSOR_PIN, INPUT);
  pinMode(BLOCK_START_G1_LED, OUTPUT);
  pinMode(BLOCK_START_R1_LED, OUTPUT);
  pinMode(BLOCK_END_G2_LED, OUTPUT);
  pinMode(BLOCK_END_R2_LED, OUTPUT);
  pinMode(BLOCK_OCCUPIED_SIGNAL_PIN, OUTPUT);
  pinMode(PRIVIOUS_BLOCK_REC_SIGNAL_PIN, INPUT);
  pinMode(NEXT_BLOCK_REC_SIGNAL_PIN, INPUT);

}

void loop() {

  blockStartingSensorVal = analogRead(BLOCK_STARTING_SENSOR_PIN);
  blockEndingSensorVal = analogRead(BLOCK_ENDING_SENSOR_PIN);
  prevBlockOccupiedSignalVal = analogRead(PRIVIOUS_BLOCK_REC_SIGNAL_PIN);
  nxtBlockOccupiedSignalVal = analogRead(NEXT_BLOCK_REC_SIGNAL_PIN);

  if (displayOn) {
    display();
  }

  delay(SENSOR_COMP_VALUE);

  switch (signalState) {
    case CURRENT_UNOCCUPIED_BLOCK:
      unOccupiedBlock(blockStartingSensorVal, blockEndingSensorVal,
                      prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
      break;
    case CURRENT_UNOCCUPIED_NEXT_OCCUPIED:
      unOccupiedNextBlockOccupied(blockStartingSensorVal, blockEndingSensorVal,
                                  prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
      break;
    case CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED:
      unOccupiedPreviousBlockOccupied(blockStartingSensorVal, blockEndingSensorVal,
                                      prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
      break;
    case CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED:
      unOccupiedPreviousAndNextBlockOccupied(blockStartingSensorVal, blockEndingSensorVal,
                                             prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
      break;
    case OCCUPYING_FROM_START:
      occupyingFromStartOfBlock(blockStartingSensorVal, blockEndingSensorVal);
      break;
    case OCCUPYING_FROM_END:
      occupyingFromEndOfBlock(blockStartingSensorVal, blockEndingSensorVal);
      break;
    case OCCUPIED_BLOCK:
      occupiedBlock(blockStartingSensorVal, blockEndingSensorVal);
      break;
  }
}


void unOccupiedBlock(int blockStartingSensorVal, int blockEndingSensorVal,
                     int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedBlock");

  blockStartGreen1On();
  blockEndGreen2On();

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0);
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;
  }
}

void unOccupiedNextBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
                                 int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedNextBlockOccupied");

  blockStartGreen1On();
  blockEndYellow2On();

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0);
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_BLOCK;//block not occupied No adjacent blocks occupied
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;
  }
}

void unOccupiedPreviousBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
                                     int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedPreviousBlockOccupied");

  blockStartYellow1On();
  blockEndGreen2On();

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0);
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_BLOCK;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;
  }
}

void unOccupiedPreviousAndNextBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
    int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedPreviousAndNextBlockOccupied");

  blockStartYellow1On();
  blockEndYellow2On();

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0);
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_BLOCK;//block not occupied No adjacent blocks occupied
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;
  }
}

void occupyingFromStartOfBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupyingFromStartOfBlock");

  blockStartRed1On();
  blockEndRed2On();

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE);
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE) && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPIED_BLOCK;
  }
}

void occupyingFromEndOfBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupyingFromEndOfBlock");

  blockStartRed1On();
  blockEndRed2On();

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE);
  delay(SENSOR_COMP_VALUE);

  if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPIED_BLOCK;
  }
}


void occupiedBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupiedBlock");

  blockStartRed1On();
  blockEndRed2On();

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE);
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_BLOCK;
  }
}

void blockStartRed1On() {
  digitalWrite(BLOCK_START_G1_LED, OFF);
  digitalWrite(BLOCK_START_R1_LED, ON);
}

void blockEndRed2On() {
  digitalWrite(BLOCK_END_G2_LED, OFF);
  digitalWrite(BLOCK_END_R2_LED, ON);
}

void blockStartYellow1On() {
  digitalWrite(BLOCK_START_G1_LED, ON);
  digitalWrite(BLOCK_START_R1_LED, ON);
}

void blockEndYellow2On() {
  digitalWrite(BLOCK_END_G2_LED, ON);
  digitalWrite(BLOCK_END_R2_LED, ON);
}

void blockStartGreen1On() {
  digitalWrite(BLOCK_START_G1_LED, ON);
  digitalWrite(BLOCK_START_R1_LED, OFF);
}

void blockEndGreen2On() {
  digitalWrite(BLOCK_END_G2_LED, ON);
  digitalWrite(BLOCK_END_R2_LED, OFF);
}

void display( ) {
  Serial.println(blockStartingSensorVal);
  Serial.println(blockStartingSensorVal);
  Serial.println(prevBlockOccupiedSignalVal);
  Serial.println(nxtBlockOccupiedSignalVal);
}
