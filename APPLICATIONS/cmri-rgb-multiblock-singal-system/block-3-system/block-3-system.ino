#include <CMRI.h>
#include <Auto485.h>

// change the address no for block no xxx
#define CMRI_ADDR 3
#define DE_PIN 2

#define sens1 A0 //Sensor 1 is setup on pin A0
#define sens2 A1 //Sensor 2 is setup on pin A1
#define  G1_LED 3 // Green Signal 1 is digital pin 3
#define  R1_LED 4// Red Signal 1 is digital pin 4
#define  G2_LED 5// Green Signal 2 is digital pin 5
#define  R2_LED 6 //Red Signal 2 is digital pin 6
#define  blockOccSignal 7 // The transmit pin for the previous and next block in the sequence
#define  prevBlockRec A2// The recieve pin for the previous block in the sequence
#define  nxtBlockRec A3// The recieve pin for the next block in the sequence
#define DELAY_VALUE 10
#define ON  HIGH
#define OFF LOW
#define SENSOR_COMP_VALUE 500
#define BLOCK_SIGNAL_REC_VALUE 300
#define BLOCK_SIGNAL_SEND_VALUE 1023

// to enable and display the console data print
const bool displayOn = false;

int sen1_A1 = -1;
int sen2_A2 = -1;
int prevBlockSignal_A3 = -1;
int nxtBlockSignal_A4  = -1;


enum SIGNAL_STATES {
  ST_G1_G2,
  ST_G1_Y2,
  ST_Y1_G2,
  ST_Y1_Y2,
  ST_R1_R2_1,
  ST_R1_R2_2,
  ST_R1_R2_3,
}; //Sets up different signal states for the entire program

SIGNAL_STATES signalState = ST_G1_G2; //Sets default state to Green and Green

Auto485 bus(DE_PIN);
CMRI cmri(CMRI_ADDR, 24, 48, bus);

void setup() {

  bus.begin(9600);

  if (displayOn) {
    Serial.begin(9600);
  }

  //Establish all of our pins at inputs or outputs

  pinMode(sens1, INPUT);
  pinMode(sens2, INPUT);
  pinMode(G1_LED, OUTPUT);
  pinMode(R1_LED, OUTPUT);
  pinMode(G2_LED, OUTPUT);
  pinMode(R2_LED, OUTPUT);
  pinMode(blockOccSignal, OUTPUT);
  pinMode(prevBlockRec, INPUT);
  pinMode(nxtBlockRec, INPUT);

}

void loop() {

  cmri.process();

  if (signalState == ST_R1_R2_1 || signalState == ST_R1_R2_2 || signalState == ST_R1_R2_3) {
    // setting sensor 0 with 1 active
    cmri.set_bit(2, 1);
  } else {
    // setting sensor 0 with 0 in-active
    cmri.set_bit(2, 0);
  }

  sen1_A1 = analogRead(sens1);
  sen2_A2 = analogRead(sens2);

  prevBlockSignal_A3 = analogRead(prevBlockRec);
  nxtBlockSignal_A4 = analogRead(nxtBlockRec);
  // Sets up the values of the different signals we will be reading

  if (displayOn) {
    display();
  }

  // Sets up the different values to be read on the serial monitor in the Arduino IDE
  delay(SENSOR_COMP_VALUE);

  switch (signalState) {
    case ST_G1_G2:
      signal_G1_G2(sen1_A1, sen2_A2, prevBlockSignal_A3, nxtBlockSignal_A4);
      break;
    case ST_G1_Y2:
      signal_G1_Y2(sen1_A1, sen2_A2, prevBlockSignal_A3, nxtBlockSignal_A4);
      break;
    case ST_Y1_G2:
      signal_Y1_G2(sen1_A1, sen2_A2, prevBlockSignal_A3, nxtBlockSignal_A4);
      break;
    case ST_Y1_Y2:
      signal_Y1_Y2(sen1_A1, sen2_A2, prevBlockSignal_A3, nxtBlockSignal_A4);
      break;
    case ST_R1_R2_1:
      signal1_R1_R2_(sen1_A1, sen2_A2);
      break;
    case ST_R1_R2_2:
      signal2_R1_R2_(sen1_A1, sen2_A2);
      break;
    case ST_R1_R2_3:
      signal3_R1_R2_(sen1_A1, sen2_A2);
      break;
      //this sets up our different loops within the main loop for our different signal states
  }
}


void signal_G1_G2(int sen1_A1, int sen2_A2,
                  int prevBlockSignal_A3, int nxtBlockSignal_A4) {

  Serial.println("signal_G1_G2");

  GREEN_1_ON(); //Sets G1_LED to ON
  GREEN_2_ON(); //Sets G2_LED to ON

  analogWrite(blockOccSignal, 0); //this will not transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((sen1_A1 > SENSOR_COMP_VALUE)
      && (sen2_A2 > SENSOR_COMP_VALUE)
      && (prevBlockSignal_A3 < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockSignal_A4 > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_G1_Y2;//block not occupied but Block B is
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_Y1_G2;//block not occupied but Block A is
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_Y1_Y2;//block not occupied but Block B and Block A are
  } else if ((sen1_A1 < SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_1;// block is occupied entered from sens1
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 < SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_2;// block is occupied entered from sens2
  }
}

void signal_G1_Y2(int sen1_A1, int sen2_A2,
                  int prevBlockSignal_A3, int nxtBlockSignal_A4) {

  Serial.println("signal_G1_Y2");

  GREEN_1_ON(); //Sets G1_LED to ON
  YELLOW_2_ON();//Sets Y2_LED to ON

  analogWrite(blockOccSignal, 0); //this will not transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((sen1_A1 > SENSOR_COMP_VALUE)
      && (sen2_A2 > SENSOR_COMP_VALUE)
      && (prevBlockSignal_A3 < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockSignal_A4 < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_G1_G2;//block not occupied No adjacent blocks occupied
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_Y1_G2;//block not occupied but Block A is
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_Y1_Y2;//block not occupied but Block B and Block A are
  } else if ((sen1_A1 < SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_1;// block is occupied entered from sens1
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 < SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_2;// block is occupied entered from sens2
  }
}

void signal_Y1_G2(int sen1_A1, int sen2_A2,
                  int prevBlockSignal_A3, int nxtBlockSignal_A4) {

  Serial.println("signal_Y1_G2");

  YELLOW_1_ON(); //Sets Y1_LED to ON
  GREEN_2_ON(); //Sets G2_LED to ON

  analogWrite(blockOccSignal, 0); //this will not transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((sen1_A1 > SENSOR_COMP_VALUE)
      && (sen2_A2 > SENSOR_COMP_VALUE)
      && (prevBlockSignal_A3 < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockSignal_A4 < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_G1_G2;//block not occupied No adjacent blocks occupied
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 < BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_G1_Y2;//block not occupied but Block B is
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_Y1_Y2;//block not occupied but Block B and Block A are
  } else if ((sen1_A1 < SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_1;// block is occupied entered from sens1
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 < SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_2;// block is occupied entered from sens2
  }
}

void signal_Y1_Y2(int sen1_A1, int sen2_A2,
                  int prevBlockSignal_A3, int nxtBlockSignal_A4) {

  Serial.println("signal_Y1_Y2");

  YELLOW_1_ON();//Sets Y1_LED to ON
  YELLOW_2_ON();//Sets Y2_LED to ON

  analogWrite(blockOccSignal, 0); //this will not transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((sen1_A1 > SENSOR_COMP_VALUE)
      && (sen2_A2 > SENSOR_COMP_VALUE)
      && (prevBlockSignal_A3 < BLOCK_SIGNAL_REC_VALUE)
      && (nxtBlockSignal_A4 < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_G1_G2;//block not occupied No adjacent blocks occupied
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 < BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 > BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_G1_Y2;//block not occupied but Block B is
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)
             && (prevBlockSignal_A3 > BLOCK_SIGNAL_REC_VALUE)
             && (nxtBlockSignal_A4 < BLOCK_SIGNAL_REC_VALUE)) {
    signalState = ST_Y1_G2;//block not occupied but Block B and Block A are
  } else if ((sen1_A1 < SENSOR_COMP_VALUE)
             && (sen2_A2 > SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_1;// block is occupied entered from sens1
  } else if ((sen1_A1 > SENSOR_COMP_VALUE)
             && (sen2_A2 < SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_2;// block is occupied entered from sens2
  }
}

void signal1_R1_R2_(int sen1_A1, int sen2_A2) {

  Serial.println("signal1_R1_R2_");

  RED_1_ON();//Sets R1_LED to ON
  RED_2_ON();//Sets R2_LED to ON

  analogWrite(blockOccSignal, BLOCK_SIGNAL_SEND_VALUE); //this will transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((sen1_A1 > SENSOR_COMP_VALUE) && (sen2_A2 < SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_3; //switched to transition Red signal state
  }
}

void signal2_R1_R2_(int sen1_A1, int sen2_A2) {

  Serial.println("signal2_R1_R2_");

  RED_1_ON();//Sets R1_LED to ON
  RED_2_ON();//Sets R2_LED to ON

  analogWrite(blockOccSignal, BLOCK_SIGNAL_SEND_VALUE); //this will transmit a signal to Block A and B
  delay(SENSOR_COMP_VALUE);

  if ((sen1_A1 < SENSOR_COMP_VALUE)
      && (sen2_A2 > SENSOR_COMP_VALUE)) {
    signalState = ST_R1_R2_3; //switched to transition Red signal state
  }
}


void signal3_R1_R2_(int sen1_A1, int sen2_A2) {

  Serial.println("signal3_R1_R2_");

  RED_1_ON();//Sets R1_LED to ON
  RED_2_ON();//Sets R2_LED to ON

  analogWrite(blockOccSignal, BLOCK_SIGNAL_SEND_VALUE); //this will transmit a signal to Block A and B
  delay(DELAY_VALUE);

  if ((sen1_A1 > SENSOR_COMP_VALUE)
      && (sen2_A2 > SENSOR_COMP_VALUE)) {
    signalState = ST_G1_G2; //switched to Green unoccupied signal
  }
}

void RED_1_ON() {
  digitalWrite(G1_LED, OFF);
  digitalWrite(R1_LED, ON);
}

void RED_2_ON() {
  digitalWrite(G2_LED, OFF);
  digitalWrite(R2_LED, ON);
}

void YELLOW_1_ON() {
  digitalWrite(G1_LED, ON);
  digitalWrite(R1_LED, ON);
}

void YELLOW_2_ON() {
  digitalWrite(G2_LED, ON);
  digitalWrite(R2_LED, ON);
}

void GREEN_1_ON() {
  digitalWrite(G1_LED, ON);
  digitalWrite(R1_LED, OFF);
}

void GREEN_2_ON() {
  digitalWrite(G2_LED, ON);
  digitalWrite(R2_LED, OFF);
}

void display( ) {
  Serial.println(sen1_A1);
  Serial.println(sen1_A1);
  Serial.println(prevBlockSignal_A3);
  Serial.println(nxtBlockSignal_A4);
}
