# NMRA-DCC-ACCSSORY-DECODER

---

![img](/DOCUMENTS/DCC-ACCSSORY-DECODER/Nmra-Dcc-Accssory-Decoder-Basic/image/6N137-octocupler.JPG)
![img](/DOCUMENTS/DCC-ACCSSORY-DECODER/Nmra-Dcc-Accssory-Decoder-Basic/image/dcc-decoder-circuits.png)
![img](/DOCUMENTS/DCC-ACCSSORY-DECODER/Nmra-Dcc-Accssory-Decoder-Basic/image/circuit_connection.JPG)
![img](/DOCUMENTS/DCC-ACCSSORY-DECODER/Nmra-Dcc-Accssory-Decoder-Basic/image/circuit.JPG)




## Connections details 
```
connect the 6N137 octocopolr 
connect the dcc track 1 and track 2 to the connector on breadboard 
connect the 1k resisstor to the track 1 line on breadboard 
then connect both track 1 to the pin 2 on octocopolr 
then connect both track 2 to the pin 3 on octocopolr 
connect the IN4148 Diaood +ve side to the pin 3 and -ve side to the pin 2 
then connect the +5v and -ve/gnd to the breadboard 
connect the gnd to the pin 6 of the cotocoplor 
connect the 10k resisotr on pin 6 and pin 7 then connect both tot he +5v on breadboard 
take jumper from pin 6 after the +5v joint and then connect to the arduino pin 2 
connect the pin 8 directly tot he +5v 

```
![img](/DOCUMENTS/DCC-ACCSSORY-DECODER/Nmra-Dcc-Accssory-Decoder-Basic/image/connections.JPG)

## NCE poewr pro 
```
press accessory button on nce procab 
then type the acessory number which is metnioned on the arduino code then 
press enter then use 1 or 2 button as shown in power cab for on and off operation 
```

## To include lib 
```
Arduino -> tool -> manage lib -> "nmradcc"

github page link 
https://github.com/mrrwa/NmraDcc
```