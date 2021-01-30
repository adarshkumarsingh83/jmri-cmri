

# CMRI CONFIGURATION IN PANEL PRO

```
JMRI PanelPro. When it is running click on edit preferences to get the following window

set the following tabs

System manufacturer = C/MRI

System connection = Serial

Setting

Serial port: (select the port your arduino is connected to, you will find this on the arduino IDE)

Connection Prefix: C

Connection Name: (what ever you want to call it)

Also click on additional connection box and select the Baud rate to 9600 bps

```

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pca9685-servo-turnout/connection-details.png)

```
## connection details 
5v power supply to pca9685 board directly 
sda and scl from arudino to pca9685 first board only 
5v and gnd from arduino to pda9685 vcc and gnd 


JMRI 
Tools -> tables -> turnout -> add 

## BOARD NO 1 WITH ADDRESS 40 
-------------------------------
board no 1 with address 40  servo position 0 will be => 1001  use 1 bit study state 
board no 1 with address 40  servo position 2 will be => 1002  use 1 bit study state
.
.
.
..... continue ......
board no 1 with address 40  servo position 16 will be => 1016  use 1 bit study state
```

### CMRI library

- https://github.com/madleech/ArduinoCMRI

### RS485 library

- https://github.com/madleech/Auto485


### PCA9685 library
- https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-single-pca9685-servo-turnout/img.jpg)