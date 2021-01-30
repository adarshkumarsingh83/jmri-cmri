

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

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-multi-pca9685-servo-turnout/pca9685%20soldering%20address%20chart.png)

```

soldering address calculation 
------------------------------------
1 + A5    A4    A3    A2    A1   A0
    32    16    8      4    2     1
------------------------------------

by deafult if nothings is solded then it will be 1 + 0 = 1 board 
AO 1st position from right is solded then it will be 1+1 = 2 board 
A1 2nd position from right is solded then it will be 2+1 = 3 board 
A0 and A1 1st and 2nd from right is solded then it will be 2+1+1 = 4 board 



```
NOTE see the soldering chart above 

### CMRI library

- https://github.com/madleech/ArduinoCMRI

### RS485 library

- https://github.com/madleech/Auto485


### PCA9685 library
- https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library


![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/cmri-pca9685-turnout-using-servo/img.jpg)