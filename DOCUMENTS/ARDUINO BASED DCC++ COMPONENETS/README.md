

# ArduinoCMRI
---


## Requirements
---
* JMRI -- http://jmri.org/

### Installation of CMRI 
```

CMRI library
https://github.com/madleech/ArduinoCMRI

Download the ZIP archive (https://github.com/madleech/ArduinoCMRI/zipball/master) and extract it to your Arduino folder under `libraries/CMRI`.

Restart the Arduino IDE and you should see in File > Examples > CMRI entires for hello world and an input/output example.
```

### Code Examples
----
```
Here is the 'hello\_world' example program, included in the download:

    #include <CMRI.h>
    
    CMRI cmri;
    
    void setup() {
      Serial.begin(9600, SERIAL_8N2); // SERIAL_8N2 to match what JMRI expects CMRI hardware to use
      pinMode(13, OUTPUT);
    }
    
    void loop() {
      cmri.process();
      digitalWrite(13, cmri.get_bit(0));
    }

This connects a Light in JMRI to the built in LED on your Arduino. Toggle the light in JMRI and your Arduino will light up.

The code is pretty simple. `#include <CMRI.h>` includes the library, while `CMRI cmri();` creates a new CMRI object with default values (address = 0, 24 inputs to PC, and 48 outputs from PC). The `Serial.begin` and `pinMode` lines set up our serial port and tell the LED pin that it's going to be an output.

The main loop is where the magic happens. `cmri.process()` receives data from the PC and processes it automatically, responding to the PC if required, and updating it's internal state ready for us to read the data back out.

To access the data we sent it, we use the `cmri.get_bit(n)` function to get the value of bit number *n*.

If you wanted to extend this demo to transmit data back to the PC, all you need to do is connect your digital inputs to `cmri.set_bit(n, value)` calls, and the `cmri.process()` function will take care of the rest.
	
```

Documentation
-------------
**CMRI(unsigned int address = 0, unsigned int input\_bits = 24, unsigned int output\_bits = 48)**
Creates a new CMRI object. The default values will create a device that matches the capabilities of an SMINI node. If you want to bind to a different node address, or address more or less inputs, you can alter it here. The maximum combined number of addressable inputs and outputs is 2048 (C/MRI limitation). The library will work fine with any number of inputs and outputs, it will simply ignore out-of-range data.

**void set\_address(unsigned int address)**
Sets the address of the C/MRI node.

**char process()**
Reads in available data from the serial port and acts accordingly:
* For POLL requests, it replies with the current state of the input data.
* For INIT requests, it does nothing.
* For SET/TRANSMIT (T) requests, it updates the output data.

Return value is NULL for no valid packet received, or one of CMRI::INIT, CMRI::SET, CMRI::POLL depending on the packet type received.

**bool process\_char(char c)**
Similar to the CMRI::process method, but lets you manage the serial data yourself. Use this if you are processing more than 1 CMRI node in a system.

Return value is true if a valid packet has been received and processing of it has finished. Otherwise it returns false.

**void transmit()**
Transmits the current state of the input data back to the PC. Creates a CMRI::GET packet.

**bool get\_bit(int n)**
Reads a bit from of the last valid input data received. Use this to update your signals, points, etc.

**char get\_byte(int n)**
Reads an entire byte from the input buffer. Use this with shiftOut and some shift registers to vastly expand your I/O capabilities.

**bool set\_bit(int n, bool b)**
Updates the output buffer to the specified value. Data will be transmitted to the PC either when transmit() is called, or when the next POLL packet is received.

**bool set\_byte(int n, char b)**
Updates an entire byte of the output buffer. Use this with shiftIn and some shift registers to add many extra digital inputs to your system.

---

## configuration in panel pro
```
start up JMRI PanelPro. When it is running click on edit preferences to get the following window

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

# RS485 library

---

### Installation of 485 cmri connector lib 
---

```
RS485 library
https://github.com/madleech/Auto485
``` 

### Code Examples
----
```
#include <CMRI.h>

#include<Auto485.h>

#define CMRI_ADDR 1

#define LED 13

#define DE_PIN 2

Auto485 bus(DE_PIN); // arduino pin 2 for DE and RE pins

CMRI cmri(CMRI_ADDR, 24, 48, bus); // defaults to a SMINI with address 0. SMINI = 24 inputs, 48 outputs

void setup() {
     pinMode(LED, OUTPUT);
     bus.begin(9600);
}

void loop() {

     cmri.process();
 
     // 2: update output. Reads bit 0 of T packet and sets the LED to this
     digitalWrite(LED, cmri.get_bit(0));

}


We start off by defining the Driver Enable pin (DE_PIN), and Receiver Enable pin (RE_PIN). Usually these pins will be connected together on the MAX485, so you can just use the same pin here.

Next we initialise the bus at 9600bps, just like you would with Serial.begin(9600). Then we print out some text using .println(...). Println handles the bus state for us, changing to TX mode then back to RX mode.

In our main loop we check if any input is available, and if it is, we set the bus to TX mode, write out the data, and return to RX mode.

```

Documentation
-------------
**Auto485(int DE_pin)**
Creates a new Auto485 object. The Driver and Receiver Enable pins on the MAX485 are connected together.

**Auto485(int DE_pin, int RE_pin)**
Creates a new Auto485 object. The Driver and Receiver Enable pins on the MAX485 are connected to separate pins on the Arduino.

**Auto485(int DE_pin, int RE_pin, HardwareSerial serial_port)**
Creates a new Auto485 object using the specified serial port. Usually the defaults are fine (Serial on most boards, Serial1 on the Leonardo and other USBCOM boards). If you are using a Mega with multiple serial ports this lets you choose which serial port to use.

**Auto485::TX**, **Auto485::RX**
These are constants to let you toggle the mode of the bus.

**begin(baud), begin(baud, config)**
Initiate a serial connection at the given speed, and optionally with the given config settings (e.g. `SERIAL_8N2` to use two stop bits, etc).

**set_mode(Auto485::TX)**, **set_mode(Auto485::RX)**
Manually change to transmit or receive mode. When returning to receive mode, the function will pause until all pending serial data has been sent.

**write(...)**, **print(...)**
When in receive mode, the first call to any output functions will change to transmit mode, then send out the data as expected. It handles all the formatting options of the regular Arduino `print` and `write` functions.

**flush()**
Finish writing data, then switch to receive mode. Usually the serial writing functions happen asynchronously, with no delay while the data is sent out the serial port. When we're operating in half duplex mode though, we need to wait for the data to finish being sent before we change the mode of the bus. By calling `.flush()` we ensure there is no unsent data in the buffer. Once all pending data has been sent, we automatically switch back to receive mode!

**println(...)**
Like the `write(...)` and `print(...)` functions, calling `println(...)` will automatically switch to transmit mode. Unlike the lower-level functions though, println will return to receive mode at the end of the line. This means you can easily print simple messages to the bus and everything operates as expected, but if you're sending data byte-by-byte, that functionality if there too and Auto485 won't toggle between RX and TX for every single byte you send.


