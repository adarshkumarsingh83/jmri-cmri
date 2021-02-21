#include <Wire.h>

#define BLOCK_STARTING_SENSOR_PIN A0 //Sensor 1 is setup on pin A0
#define BLOCK_ENDING_SENSOR_PIN A1 //Sensor 2 is setup on pin A1
#define BLOCK_OCCUPIED_SIGNAL_PIN 7 // The transmit pin for the previous and next block in the sequence
#define PRIVIOUS_BLOCK_REC_SIGNAL_PIN A2// The recieve pin for the previous block in the sequence
#define NEXT_BLOCK_REC_SIGNAL_PIN A3// The recieve pin for the next block in the sequence
#define DELAY_VALUE 300
#define SENSOR_COMP_VALUE 500
#define BLOCK_SIGNAL_REC_VALUE 300
#define BLOCK_SIGNAL_SEND_VALUE 1023

// to enable and display the console data print
const bool displayOn = false;

int blockStartingSensorVal = -1;
int blockEndingSensorVal = -1;
int prevBlockOccupiedSignalVal = -1;
int nxtBlockOccupiedSignalVal  = -1;

const int address = 0x20;          // PCF8574 device 1
const int LED_Pattern_ON = 0x00;  // LED Sequence Start pattern, one LED on .   =>  0b0000000000000000
const int LED_Pattern_OFF = 0xFFFF;  // LED Sequence Start pattern, one LED off =>  0b1111111111111111

enum SIGNAL_STATES {
  CURRENT_AND_AJUCENT_UNOCCUPIED_BLOCK,
  CURRENT_UNOCCUPIED_NEXT_OCCUPIED,
  CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED,
  CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED,
  OCCUPYING_FROM_START,
  OCCUPYING_FROM_END,
  OCCUPIED_BLOCK,
}; 

SIGNAL_STATES signalState = CURRENT_AND_AJUCENT_UNOCCUPIED_BLOCK; 

int sum = 0;

void setup() {

  // I2C init
  Wire.begin();

  if (displayOn) {
    Serial.begin(9600);
  }


  pinMode(BLOCK_STARTING_SENSOR_PIN, INPUT);
  pinMode(BLOCK_ENDING_SENSOR_PIN, INPUT);
  pinMode(BLOCK_OCCUPIED_SIGNAL_PIN, OUTPUT);
  pinMode(PRIVIOUS_BLOCK_REC_SIGNAL_PIN, INPUT);
  pinMode(NEXT_BLOCK_REC_SIGNAL_PIN, INPUT);


  // Turn off all GPIO pins on both I2C expanders by writing all "1"
  Wire.beginTransmission(address);
  Wire.write(0xFF);
  Wire.endTransmission();
}

void loop() {

  blockStartingSensorVal = analogRead(BLOCK_STARTING_SENSOR_PIN);
  blockEndingSensorVal = analogRead(BLOCK_ENDING_SENSOR_PIN);
  prevBlockOccupiedSignalVal = analogRead(PRIVIOUS_BLOCK_REC_SIGNAL_PIN);
  nxtBlockOccupiedSignalVal = analogRead(NEXT_BLOCK_REC_SIGNAL_PIN);

  if (displayOn) {
    display();
  }

  delay(DELAY_VALUE);

  switch (signalState) {
    case CURRENT_AND_AJUCENT_UNOCCUPIED_BLOCK:
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

  // Sets BLOCK_START_G1_LED to ON
  // Sets BLOCK_END_G2_LED to ON
  lightOperation( false, true, false, false, true, false);

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0); 
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
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;//block not occupied but previous block is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;//block not occupied but adjucent block are 
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occuping entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occuping entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void unOccupiedNextBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
                                 int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedNextBlockOccupied");

  // Sets BLOCK_START_G1_LED to ON
  // Sets Y2_LED to ON
  lightOperation( false, true, false,  true, true, false);

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0);
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_AND_AJUCENT_UNOCCUPIED_BLOCK;//block not occupied No adjacent blocks occupied
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;//block not occupied but previous block is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;//block not occupied but adjucent block are 
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occuping entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occuping entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void unOccupiedPreviousBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
                                     int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedPreviousBlockOccupied");

  // Sets Y1_LED to ON
  // Sets BLOCK_END_G2_LED to ON
  lightOperation( true, true, false, false, true, false);

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0); 
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_AND_AJUCENT_UNOCCUPIED_BLOCK;//block not occupied No adjacent blocks occupied
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;//block not occupied but next block is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_NEXT_OCCUPIED;//block not occupied but adjucent block are 
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occuping entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occuping entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void unOccupiedPreviousAndNextBlockOccupied(int blockStartingSensorVal, int blockEndingSensorVal,
    int prevBlockOccupiedSignalVal, int nxtBlockOccupiedSignalVal) {

  Serial.println("unOccupiedPreviousAndNextBlockOccupied");

  // Sets Y1_LED to ON
  // Sets Y2_LED to ON
  lightOperation(true, true, false,  true, true, false);

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, 0); 
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)
      && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_AND_AJUCENT_UNOCCUPIED_BLOCK;//block not occupied No adjacent blocks occupied
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_NEXT_OCCUPIED;//block not occupied but Block B is
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)
             && (prevBlockOccupiedSignalVal > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockOccupiedSignalVal < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = CURRENT_UNOCCUPIED_PRIVIOUS_OCCUPIED;//block not occupied but adjucent block are 
  } else if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
             && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_START;// block is occuping entered from BLOCK_STARTING_SENSOR_PIN
  } else if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
             && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPYING_FROM_END;// block is occuping entered from BLOCK_ENDING_SENSOR_PIN
  }
}

void occupyingFromStartOfBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupyingFromStartOfBlock");

  // Sets BLOCK_START_R1_LED to ON
  // Sets BLOCK_END_R2_LED to ON
  lightOperation( true, false, false,  true, false, false);

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE); 
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE) && (blockEndingSensorVal < SENSOR_COMP_VALUE)) {
    signalState = OCCUPIED_BLOCK; 
  }
}

void occupyingFromEndOfBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupyingFromEndOfBlock");

  // Sets BLOCK_START_R1_LED to ON
  // Sets BLOCK_END_R2_LED to ON
  lightOperation( true, false, false,  true, false, false);

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE); 
  delay(SENSOR_COMP_VALUE);

  if ((blockStartingSensorVal < SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = OCCUPIED_BLOCK; //switched to transition OCCUPIED_BLOCK
  }
}


void occupiedBlock(int blockStartingSensorVal, int blockEndingSensorVal) {

  Serial.println("occupiedBlock");

  // Sets BLOCK_START_R1_LED to ON
  // Sets BLOCK_END_R2_LED to ON
  lightOperation( true, false, false,  true, false, false);

  analogWrite(BLOCK_OCCUPIED_SIGNAL_PIN, BLOCK_SIGNAL_SEND_VALUE); 
  delay(DELAY_VALUE);

  if ((blockStartingSensorVal > SENSOR_COMP_VALUE)
      && (blockEndingSensorVal > SENSOR_COMP_VALUE)) {
    signalState = CURRENT_AND_AJUCENT_UNOCCUPIED_BLOCK; 
  }
}

/*
  postions 7 6 5 4 3 2 1 0
  value    1 1 1 1 1 1 1 1   off
  value    0 0 0 0 0 0 0 0   on

  led pin on the pcf8574

       p0 green_1
       p1 yellow_1
       p2 red_1
       p3 green_1
       p4 yellow_1
       p5 red_1
*/

void lightOperation( bool red1, bool green1, bool blue1,
                     bool red2, bool green2, bool blue2) {

  Serial.println(green1);
  Serial.println(blue1);
  Serial.println(red1);

  Serial.println(green2);
  Serial.println(blue2);
  Serial.println(red2);
  Serial.println();

  if (!blue2) {
    sum += 32;
  } else {
    Serial.println("blue2");
  }
  if (!green2) {
    sum += 16;
  } else {
    Serial.println("green2");
  }

  if (!red2) {
    sum += 8;
  } else {
    Serial.println("red2");
  }

  if (!blue1) {
    sum += 4;
  } else {
    Serial.println("blue1");
  }

  if (!green1) {
    sum += 2;
  } else {
    Serial.println("green1");
  }

  if (!red1) {
    sum += 1;
  } else {
    Serial.println("red1");
  }

  Wire.beginTransmission(address);
  Wire.write(sum);
  Wire.endTransmission();
  sum = 0 ;
}

void display( ) {
  Serial.println(blockStartingSensorVal);
  Serial.println(blockStartingSensorVal);
  Serial.println(prevBlockOccupiedSignalVal);
  Serial.println(nxtBlockOccupiedSignalVal);
}
