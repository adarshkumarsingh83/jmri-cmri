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
const char* SS_ID = "adarsh_radha_2G"; // ESP8266 do not support 5G wifi connection
const char* WIFI_PWD = "*******";
const char*  MQTT_USER = "adarsh";
const char*  MQTT_PWD = "password";

// MQTT
// find this ip using ipconfig or check in router
const char*  MQTT_SERVER = "192.168.0.188";

// change the node "number/name"  based on the node default is 1 in this
const char* JMRI_MQTT_TOPIC = "/trains/track/#";
const String JMRI_MQTT_SENSOR_TOPIC = "/trains/track/sensor/";

// change the node "number/name"  based on the node
const char* CLIENT_ID = "JMRI_NODE_ESP8266_PUBLISHING_1";

#define BROAD_RATE 115200
#define DELAY_TIME 5000
#define ACTIVE "ACTIVE"
#define INACTIVE "INACTIVE"
#define ACT "AC"

#endif
