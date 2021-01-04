# jmri-cmri

---

### jmri-cmri


### SETUP 
----

# ArduinoCMRI
---


Requirements
------------
* JMRI -- http://jmri.org/
* An Arduino -- http://arduino.cc/ -- More modern Arduino boards (such as the Uno) are supported  now!

Installation
------------
Download the ZIP archive (https://github.com/madleech/ArduinoCMRI/zipball/master) and extract it to your Arduino folder under `libraries/CMRI`.

Restart the Arduino IDE and you should see in File > Examples > CMRI entires for hello world and an input/output example.


Code Examples
-------------
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
	
