#ifndef Config_h
#define Config_h
#include "Arduino.h"

// ESP8266 do not support 5G wifi connection
const char* WIFI_SSID = "adarsh_radha_2G"; 
const char* WIFI_PASSWROD = "*******";

// IP OF THE SERVER MACHINE WHERE SPRING TRANSFORMER IS RUNNING 
const char* SERVER_URL = "http://192.168.0.188:8090/amt/node/1";
const char* NODE_ID="1";

#endif
