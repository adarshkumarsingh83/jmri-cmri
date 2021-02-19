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

---

### CMRI CONFIGURATION IN PANEL PRO
```
CMRI PanelPro. When it is running click on edit preferences ->  connections to get the following window

set the following tabs

System manufacturer = C/MRI

System connection = Serial

Setting

Serial port: (select the port your arduino is connected to, you will find this on the arduino IDE)

Connection Prefix: C

Connection Name: (what ever you want to call it)

Also click on additional connection box and select the Baud rate to 9600 bps

```

---

## USIC_SUSIC NODE TYPE WITH 24BIT CARD 72 OUTPUT AND 24 INPUT 


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/1-24input-72output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/node-24input-72output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/led-24input-72out.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/sensor-24input-72out.png)


### NODE CONFIGUATION IN JMRI 
```
CMRI PanelPro. ->  preferences ->  connections to get the following window

click on add node 

provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: USIC_SUSIC 

Card Size: 24 Bit 

Please select Card Type:  0 OutputCard 
                          1 OutputCard
                          2 OutputCard
                          3 InputCard 

Description: 72Output and 24 Input 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 
```

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

### LED CONFIGURATION IN JMRI 
```
Open Panel pro 
tools -> table -> light ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


NOTE : In Arduino code address for the light will start from 0 but in jmri it will start from 1 
Example: 
cmri.get_bit(0);
param is light address 
but while configuring the light will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1072 in jmri for led 
```

### SENSOR CONFIGURATION IN JMRI
```
Open Panel pro 
tools -> table -> sensors ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


   click on sensors window on top menu Defaults -> Initial Sensor state -> provide inactive in open popup window and -> click on "ok" button 


NOTE : In Arduino code address for the sensor will start from 0 but in jmri it will start from 1 
Example: 
cmri.set_bit(0, xxx);
1st param is sensor address and 2nd is the value we cant to send to jmri 
but while configuringg the sensor will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1024 in jmri for sensors 
```

---


## USIC_SUSIC NODE TYPE WITH 24BIT CARD 48 OUTPUT AND 48 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/2-48input-48-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/node-48input-48output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/led-48input-48out.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/sensor-48input-48out.png)



### NODE CONFIGUATION IN JMRI 
```
CMRI PanelPro. ->  preferences ->  connections to get the following window

click on add node 

provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: USIC_SUSIC 

Card Size: 24 Bit 

Please select Card Type:  0 OutputCard 
                          1 OutputCard
                          2 InputCard
                          3 InputCard 

Description: 48Output and 48Input 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 
```

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

### LED CONFIGURATION IN JMRI 
```
Open Panel pro 
tools -> table -> light ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


NOTE : In Arduino code address for the light will start from 0 but in jmri it will start from 1 
Example: 
cmri.get_bit(0);
param is light address 
but while configuring the light will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1048 in jmri for led 
```

### SENSOR CONFIGURATION IN JMRI
```
Open Panel pro 
tools -> table -> sensors ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


   click on sensors window on top menu Defaults -> Initial Sensor state -> provide inactive in open popup window and -> click on "ok" button 


NOTE : In Arduino code address for the sensor will start from 0 but in jmri it will start from 1 
Example: 
cmri.set_bit(0, xxx);
1st param is sensor address and 2nd is the value we cant to send to jmri 
but while configuringg the sensor will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1048 in jmri for sensors 
```

---

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 24 OUTPUT AND 72 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/3-72input-24-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/node-72input-24outputs.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/led-72input-24-output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/sensor-72input-24-output.png)



### NODE CONFIGUATION IN JMRI 
```
CMRI PanelPro. ->  preferences ->  connections to get the following window

click on add node 

provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: USIC_SUSIC 

Card Size: 24 Bit 

Please select Card Type:  0 OutputCard 
                          1 InputCard
                          2 InputCard
                          3 InputCard 

Description: 24Output and 72Input 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 
```


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

### LED CONFIGURATION IN JMRI 
```
Open Panel pro 
tools -> table -> light ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


NOTE : In Arduino code address for the light will start from 0 but in jmri it will start from 1 
Example: 
cmri.get_bit(0);
param is light address 
but while configuring the light will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1024 in jmri for led 
```

### SENSOR CONFIGURATION IN JMRI
```
Open Panel pro 
tools -> table -> sensors ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


   click on sensors window on top menu Defaults -> Initial Sensor state -> provide inactive in open popup window and -> click on "ok" button 


NOTE : In Arduino code address for the sensor will start from 0 but in jmri it will start from 1 
Example: 
cmri.set_bit(0, xxx);
1st param is sensor address and 2nd is the value we cant to send to jmri 
but while configuringg the sensor will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1072 in jmri for sensors 
```

---

## USIC_SUSIC NODE TYPE WITH 32BIT CARD 96 OUTPUT AND 96 INPUT 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/4-96input-96output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/node-96input-96output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/led-96input-96output.png)
![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-usic-susic-24bit-card-node/image/sensor-96input-96output.png)



### NODE CONFIGUATION IN JMRI 
```
CMRI PanelPro. ->  preferences ->  connections to get the following window

click on add node 

provide the node address bases on arduino stetch 
Example below 
 #define CMRI_ADDR 1

in Node Address (UA) textbox 
Node Type: USIC_SUSIC 

Card Size: 24 Bit 

Please select Card Type:  0 OutputCard 
                          1 OutputCard
                          2 OutputCard
                          3 OutputCard 
                          4 InputCard
                          5 InputCard
                          6 InputCard
                          7 InputCard

Description: 24Output and 72Input 

 after providing above information click on "addd node" and then click on "done"
 then click on save and restart the panel pro 
```


### Code 

```

#include <CMRI.h>
#include<Auto485.h>

#define CMRI_ADDR 1
#define RED_LED_PIN 13
#define GREEN_LED_PIN 12
#define SENSOR_1 11
#define SENSOR_2 10

#define DE_PIN 2

// arduino pin 2 for DE and RE pins
Auto485 bus(DE_PIN); 

// a USIC_SUSIC with address 0. USIC_SUSIC = 96 inputs, 96 outputs
CMRI cmri(CMRI_ADDR, 96, 96, bus); 

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
  cmri.set_bit(95, !digitalRead(SENSOR_2));
}
```

### LED CONFIGURATION IN JMRI 
```
Open Panel pro 
tools -> table -> light ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


NOTE : In Arduino code address for the light will start from 0 but in jmri it will start from 1 
Example: 
cmri.get_bit(0);
param is light address 
but while configuring the light will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1096 in jmri for led 
```

### SENSOR CONFIGURATION IN JMRI
```
Open Panel pro 
tools -> table -> sensors ->  
click on "add" sensor button 
   Systemn Connection : C/MRI 
   Hardware Address : 1001 // based on Arduino sketch 
   User Name : provide any information 

   Click on "Create" Button 


   click on sensors window on top menu Defaults -> Initial Sensor state -> provide inactive in open popup window and -> click on "ok" button 


NOTE : In Arduino code address for the sensor will start from 0 but in jmri it will start from 1 
Example: 
cmri.set_bit(0, xxx);
1st param is sensor address and 2nd is the value we cant to send to jmri 
but while configuringg the sensor will start the address by 1001 in which 1000 is arduino address and 1 is the sensor address 

1001 and 1096 in jmri for sensors 
```