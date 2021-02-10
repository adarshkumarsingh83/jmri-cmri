# RGB Multblock decection system 

--- 

![img](https://github.com/adarshkumarsingh83/jmri-cmri/blob/main/APPLICATIONS/rgb-led-multiblock-signal-system/CONNECTIONS.JPG)

## Connection Deatils 

```
  
Assumption: 
Train can travel from both direction of the block 
every block start will have IR sensor and end will also have IR sensor 
train has to click both 1st and 2nd IR sensor one by one either of the direction otherwise it will not show as UnOccupoied even train left the block 

1.connection the +5v and gnd to the breadboard 
2.connection led1 and led2 to the breadboard gnd long leg (common cathod rgb led) 
3. then connection 2 resistor to the red and green led of the rgb led for both led1 and led2 
4. then connect the green long leg of led1 to the 2 pin in arduino  
5. then connection the red long  leg led11 to the 3 pin in arduino  
6. then connect the green long leg of led2 to the 4 pin in arduino  
7. then connect the red long  leg led12 to the 5 pin in arduino  
8. then connect the IR sensor 1 and 2 to the bread board 
9. then connect the vcc and gnd to the IR sensor from breadboard +5 and gnd 
10 then connect the IR sensor1 out to the A0 pin in arduino 
11 then connect the IR sensor2 out to the A1 pin in arduino 
12. then connect pin 6 on arduino to the breadboard column which will go the the previous and next block for occupied signal 
13. take one connection to the previous block arduino and connect to the A3 pin of that 
14. take one connection to the next block arduion and connect to the A2 pin of that 
15. take previous block incomming occupied singal connection to the pin A2 of the arduino 
16. take next block incomming occupied sinal cconnection to the pin A3 of the arduino 
17. take the connection from gnd pin from arudino to the next and previous block gnd pins connect all gnd to tmake common ground bus for entre block system. 

```

