
/*
   Adarsh Model Trains
   Developed by Adarsh kumar
   Support adarshmodeltrains@gmail.com
*/

#ifndef Config_h
#define Config_h
#include "Arduino.h"

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "adarsh_radha_2G"; // ESP8266 do not support 5G wifi connection
const char* wifi_password = "@Endless@1309";
const char* mqtt_username = "adarsh";
const char* mqtt_password = "password";

// MQTT
// find this ip using ipconfig or check in router
const char* mqtt_server = "192.168.0.188"; 

// change the node "number/name"  based on the node default is 1 in this 
const char* mqtt_topic = "/amt/node/1/#";
const char* mqtt_topic_light = "/amt/node/1/light/";
const char* mqtt_topic_turnout = "/amt/node/1/turnout/";
const char* mqtt_topic_signalhead = "/amt/node/1/signal/";

// change the node "number/name"  based on the node 
const char* clientID = "JMRI_SUBSCRIBER_NODE_ESP8266_1";

#define BROAD_RATE 115200
#define DELAY_TIME 1000

#endif
