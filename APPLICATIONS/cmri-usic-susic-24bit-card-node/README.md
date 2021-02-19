# CMRI USIC_SUSIC 24BIT CARD NODE TYPE 

---- 

```
 every card is having 24 bit so number of card added to the input or output
 it will add 24 to the total of that 
 eg 
    24 added to input then currentinput + 24 
    24 added to ouput then currentoutput + 24   
 ```

## connections 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/connection.JPG)

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

## USIC_SUSIC NODE TYPE WITH 24BIT CARD 72 OUTPUT AND 24 INPUT 


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/1-24input-72output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/node-24input-72output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/led-24input-72out.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/sensor-24input-72out.png)

### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 24 inputs, 72 outputs
// CMRI cmri(CMRI_ADDR, 24, 72, bus); 

#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CCMRI cmri(CMRI_ADDR, 24, 72, bus);  //  a USIC_SUSIC with address 0. USIC_SUSIC = 24 inputs, 72 outputs

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
  digitalWrite(RED_LED_PIN, cmri.get_bit(71));

  cmri.set_bit(0, !digitalRead(SENSOR_1));
  cmri.set_bit(23, !digitalRead(SENSOR_2));
}
```

## USIC_SUSIC NODE TYPE WITH 24BIT CARD 48 OUTPUT AND 48 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/2-48input-48-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/node-48input-48output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/led-48input-48out.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/sensor-48input-48out.png)

### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 48 inputs, 48 outputs
// CMRI cmri(CMRI_ADDR, 48, 48, bus); 


#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 48, 48, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 48 inputs, 48 outputs

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
  digitalWrite(RED_LED_PIN, cmri.get_bit(47));

  cmri.set_bit(0, !digitalRead(SENSOR_1));
  cmri.set_bit(47, !digitalRead(SENSOR_2));
}
```

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 32 OUTPUT AND 96 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/3-72input-24-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/node-72input-24outputs.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/led-72input-24-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/sensor-72input-24-output.png)


### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 72 inputs, 24 outputs
// CMRI cmri(CMRI_ADDR, 72, 24, bus); 


#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 72, 24, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 72 inputs, 24 outputs

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
  digitalWrite(RED_LED_PIN, cmri.get_bit(23));

  cmri.set_bit(0, !digitalRead(SENSOR_1));
  cmri.set_bit(71, !digitalRead(SENSOR_2));
}
```