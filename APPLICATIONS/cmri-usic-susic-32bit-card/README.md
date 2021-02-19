# CMRI USIC_SUSIC 32BIT CARD NODE TYPE 

---- 

```
 every card is having 32 bit so number of card added to the input or output
 it will add 32 to the total of that 
 eg 
    32 added to input then currentinput + 32 
    32 added to ouput then currentoutput + 32 

```

## connections 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/connection.JPG)

```
connect the +5v and gnd to the breadboard 
connect the short leg of the green and red led to the common gnd line of bredboard 
connect the resistor to the long leg of the red and green led 
connect the pin 13 and pin 12 to the long resistor of red and green led 

add two IR sensors in breadboard 
add the gnd and +5v to the vcc and gnd pin of the IR sensor 
add the connection from IR sensor1 out pin to the pin11 of the mega 
add the connection from IR sensor2 out pin to the pin10 of the mega 
```

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 96 OUTPUT AND 32 INPUT 


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/1-32input-96output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/node-32input-96output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/led-32input-96out.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/sensor-32input-96out.png)

### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 32 inputs, 96 outputs
// CMRI cmri(CMRI_ADDR, 32, 96, bus); 

#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 32, 96, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 32 inputs, 96 outputs

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);  
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(95));

  cmri.set_bit(0, !digitalRead(SENSOR_1));
  cmri.set_bit(31, !digitalRead(SENSOR_2));
}
```

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 64 OUTPUT AND 64 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/2-64input-64-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/node-64input-64output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/led-64input-64out.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/sensor-64input-64out.png)

### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 64 inputs, 64 outputs
// CMRI cmri(CMRI_ADDR, 64, 64, bus); 


#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 64, 64, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 64 inputs, 64 outputs

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);

}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(63));

  cmri.set_bit(0, !digitalRead(SENSOR_1));
  cmri.set_bit(63, !digitalRead(SENSOR_2));
}
```

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 32 OUTPUT AND 96 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/3-96input-32-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/node-96input-32outputs.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/led-96input-32-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/sensor-96input-32-output.png)


### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 96 inputs, 32 outputs
// CMRI cmri(CMRI_ADDR, 96, 32, bus); 


#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 96, 32, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 96 inputs, 32 outputs

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(SENSOR_1, INPUT_PULLUP);
  pinMode(SENSOR_2, INPUT_PULLUP);
}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(31));

  cmri.set_bit(0, !digitalRead(SENSOR_1));
  cmri.set_bit(95, !digitalRead(SENSOR_2));
}
```