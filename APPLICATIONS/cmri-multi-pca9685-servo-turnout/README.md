

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

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pca9685-servo-turnout/multi_pca9685%20servo.png)

# or 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pca9685-servo-turnout/adafruit_MultiBoard_dasichain.jpg)


# soldering for pca9685 board for adddress configuation in dasi chain 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pca9685-servo-turnout/pca9685%20soldering%20address%20chart.png)

```

## connection details 
5v power supply to pca9685 board directly 
sda and scl from arudino to pca9685 first board only 
5v and gnd from arduino to pda9685 vcc and gnd 
and then dasi chain the pca9685 with board 1 to board 2 and then so on 


soldering address calculation 
------------------------------------
1 + A5    A4    A3    A2    A1   A0
    32    16    8      4    2     1
------------------------------------

by deafult if nothings is solded then it will be 1 + 0 = 1 board 
AO 1st position from right is solded then it will be 1+1 = 2 board 
A1 2nd position from right is solded then it will be 2+1 = 3 board 
A0 and A1 1st and 2nd from right is solded then it will be 2+1+1 = 4 board 
...... and so on 

NOTE see the soldering chart above 

SEE the reference doc for the PCF9685

https://learn.adafruit.com/16-channel-pwm-servo-driver?view=all

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



## BOARD NO 2 WITH ADDRESS 41
-------------------------------
board no 2 with address 41 servo position  0 will be => 1017    use 1 bit study state 
board no 2 with address 41 servo position  1 will be => 1018    use 1 bit study state 
.
.
.
..... continue ......
board no 2 with address 41 servo position  16 will be => 1032    use 1 bit study state 



## BOARD NO 3 WITH ADDRESS 42
-------------------------------
board no 3  with address 42 servo position 0 will be => 1033    use 1 bit study state 
board no 3 with asddress 42 servo position 1 will be => 1034    use 1 bit study state 
.
.
.
..... continue ......
board no 3 with asddress 42 servo position 16 will be => 1048    use 1 bit study state 



## BOARD NO 4 WITH ADDRESS 43
-------------------------------
board no 4 with address 43 servo poition 0 will be => 1049   use 1 bit study state 
board no 4 with address 43 servo poition 1 will be => 1050   use 1 bit study state 
.
.
.
..... continue ......
board no 4 with address 43 servo poition 16 will be => 1064   use 1 bit study state 


and so on till the number of board mutliplied by 16 total we can have numbers 



```

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pca9685-servo-turnout/demo.jpg)


### CMRI library

- https://github.com/madleech/ArduinoCMRI

### RS485 library

- https://github.com/madleech/Auto485


### PCA9685 library
- https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library


