# CMRI USIC_SUSIC 32BIT CARD NODE TYPE 

---- 

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
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/node-96input-32output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/image/led-96input-32-outputs.png)
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