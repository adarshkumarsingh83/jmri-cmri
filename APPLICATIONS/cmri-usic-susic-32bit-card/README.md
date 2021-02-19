# CMRI USIC_SUSIC 32BIT CARD NODE TYPE 

---- 

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 96 OUTPUT AND 32 INPUT 


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/1-32input-96output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/node-32input-96output.png)


### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 32 inputs, 96 outputs
// CMRI cmri(CMRI_ADDR, 32, 96, bus); 

#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 32, 96, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 32 inputs, 96 outputs

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(95));
}
```

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 64 OUTPUT AND 64 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/2-64input-64-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/node-64input-64output.png)

### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 64 inputs, 64 outputs
// CMRI cmri(CMRI_ADDR, 64, 64, bus); 


#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 64, 64, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 64 inputs, 64 outputs

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(63));
}
```

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 32 OUTPUT AND 96 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/3-96input-32-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-32bit-card/node-96input-32output.png)

### Code 

```
//  a USIC_SUSIC with address 0. USIC_SUSIC = 96 inputs, 32 outputs
// CMRI cmri(CMRI_ADDR, 96, 32, bus); 


#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 96, 32, bus); //  a USIC_SUSIC with address 0. USIC_SUSIC = 96 inputs, 32 outputs

void setup() {
  bus.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

}

void loop() {
  cmri.process();
  digitalWrite(GREEN_LED_PIN, cmri.get_bit(0));
  digitalWrite(RED_LED_PIN, cmri.get_bit(31));
}
```