#include <CMRI.h>
#include <Auto485.h>

// change the address no for block no xxx
#define CMRI_ADDR 3
#define DE_PIN 2

#define BLOCK_STARTING_SENSOR_PIN A0 //Sensor 1 is setup on pin A0
#define BLOCK_ENDING_SENSOR_PIN A1 //Sensor 2 is setup on pin A1
#define BLOCK_START_G1_LED 3 // Green Signal 1 is digital pin 3
#define BLOCK_START_R1_LED 4// Red Signal 1 is digital pin 4
#define BLOCK_END_G2_LED 5// Green Signal 2 is digital pin 5
#define BLOCK_END_R2_LED 6 //Red Signal 2 is digital pin 6
#define BLOCK_OCCUPIED_SIGNAL_PIN 7 // The transmit pin for the previous and next block in the sequence
#define PRIVIOUS_BLOCK_REC_SIGNAL_PIN A2// The recieve pin for the previous block in the sequence
#define NEXT_BLOCK_REC_SIGNAL_PIN A3// The recieve pin for the next block in the sequence
#define DELAY_VALUE 10
#define ON  HIGH
#define OFF LOW
#define SENSOR_COMP_VALUE 500
#define BLOCK_SIGNAL_REC_VALUE 300
#define BLOCK_SIGNAL_SEND_VALUE 1023

// to enable and display the console data print
const bool displayOn = false;

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
}; //Sets up different signal states for the entire program

SIGNAL_STATES signalState = CURRENT_UNOCCUPIED_BLOCK; //Sets default state to Green and Green

Auto485 bus(DE_PIN);
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {

  bus.begin(9600);

  if (displayOn) {
    Serial.begin(9600);
  }

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

  cmri.process();

  if (signalState == OCCUPYING_FROM_START || signalState == OCCUPYING_FROM_END || signalState == OCCUPIED_BLOCK) {
    // setting sensor 0 with 1 active
    cmri.set_bit(0, 1);
  } else {
    // setting sensor 0 with 0 in-active
    cmri.set_bit(0, 0);
  }

  blockStartingSensorVal = analogRead(BLOCK_STARTING_SENSOR_PIN);
  blockEndingSensorVal = analogRead(BLOCK_ENDING_SENSOR_PIN);

  prevBlockOccupiedSignalVal = analogRead(PRIVIOUS_BLOCK_REC_SIGNAL_PIN);
  nxtBlockOccupiedSignalVal = analogRead(NEXT_BLOCK_REC_SIGNAL_PIN);
  // Sets up the values of the different signals we will be reading

  if (displayOn) {
    display();
  }

  // Sets up the different values to be read on the serial monitor in the Arduino IDE
  delay(SENSOR_COMP_VALUE);

  switch (signalState) {
    case CURRENT_UNOCCUPIED_BLOCK:
      unOccupiedBlock(blockStartingSensorVal, blockEndingSensorVal, prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
      break;
    case CURRENT_UNOCCUPIED_NEXT_OCCUPIED:
      unOccupiedNextBlockOccupied(blockStartingSensorVal, blockEndingSensorVal, prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
      break;
    case CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED:
      unOccupiedPreviousBlockOccupied(blockStartingSensorVal, blockEndingSensorVal, prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
      break;
    case CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED:
      unOccupiedPreviousAndNextBlockOccupied(blockStartingSensorVal, blockEndingSensorVal, prevBlockOccupiedSignalVal, nxtBlockOccupiedSignalVal);
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
      //this sets up our different loops within the main loop for our different signal states
  }
}


void unOccupiedBlock(int blockStartingSensorVal, int blockEndingSensorVal,
                     int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedBlock");

  blockStartGreen1On(); //Sets BLOCK_START_G1_LED to ON
  blockEndGreen2On(); //Sets BLOCK_END_G2_LED to ON

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0); //this will not transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;//block not occupied but Block B is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;//block not occupied but Block A is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;//block not occupied but Block B and Block A are
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occupied entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occupied entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void unOccupiedNextBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
                                 int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedNextBlockOccupied");

  blockStartGreen1On(); //Sets BLOCK_START_G1_LED to ON
  blockEndYellow2On();//Sets Y2_LED to ON

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0); //this will not transmit a signal to Block A and B
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
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;//block not occupied but Block A is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;//block not occupied but Block B and Block A are
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occupied entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occupied entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void unOccupiedPreviousBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
                                     int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedPreviousBlockOccupied");

  blockStartYellow1On(); //Sets Y1_LED to ON
  blockEndGreen2On(); //Sets BLOCK_END_G2_LED to ON

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0); //this will not transmit a signal to Block A and B
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
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;//block not occupied but Block B is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;//block not occupied but Block B and Block A are
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occupied entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occupied entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void unOccupiedPreviousAndNextBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
                  int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedPreviousAndNextBlockOccupied");

  blockStartYellow1On();//Sets Y1_LED to ON
  blockEndYellow2On();//Sets Y2_LED to ON

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0); //this will not transmit a signal to Block A and B
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
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;//block not occupied but Block B is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;//block not occupied but Block B and Block A are
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occupied entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occupied entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void occupyingFromStartOfBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupyingFromStartOfBlock");

  blockStartRed1On();//Sets BLOCK_START_R1_LED to ON
  blockEndRed2On();//Sets BLOCK_END_R2_LED to ON

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE); //this will transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE) && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPIED_BLOCK; //switched to transition Red signal state
  }
}

void occupyingFromEndOfBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupyingFromEndOfBlock");

  blockStartRed1On();//Sets BLOCK_START_R1_LED to ON
  blockEndRed2On();//Sets BLOCK_END_R2_LED to ON

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE); //this will transmit a signal to Block A and B
  delay(SENSOR_COMP_VALUE);

  if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPIED_BLOCK; //switched to transition Red signal state
  }
}


void occupiedBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupiedBlock");

  blockStartRed1On();//Sets BLOCK_START_R1_LED to ON
  blockEndRed2On();//Sets BLOCK_END_R2_LED to ON

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE); //this will transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_BLOCK; //switched to Green unoccupied signal
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
