
// Global definitions

#ifndef GLOBALS_H

#define GLOBALS_H

// Slots for RAW data recording
#define SLOTS_NUMBER 20 // Number of slots
#define SLOT_SIZE 300   // Size of single slot
#define SEQ_SIZE 10     // Raw sequnece size
#define DEBUG X

#ifdef DEBUG
 // dev device (wemos)
#define RECV_PIN 13    // D7 - GPIO13
#define TRANS_PIN 14   // D5 - GPIO14
#define TRIGGER_PIN 15 // D8 - GPIO15
#define LED_PIN 2      // D4 - GPIO2
#define BUTTON_ACTIVE_LEVEL HIGH
#else
 // production device - ESP01
#define RECV_PIN 0    // D3 - GPIO0 - IR detector/demodulator
#define TRANS_PIN 3   // RX - GPIO3 - IR LED trasmitter
#define TRIGGER_PIN 2 // D4 - GPIO2 - trigger reset (press and hold after boot - 5 seconds)
//#define LED_PIN 1      // D4 - GPIO2
#define BUTTON_ACTIVE_LEVEL LOW
#endif

#define       SUFFIX_SUBSCRIBE "/sender/#"
#define            SUFFIX_WILL "/status"
#define            SUFFIX_WIPE "/sender/wipe"
#define          SUFFIX_REBOOT "/sender/reboot"
#define         SUFFIX_NC_HDMI "/sender/NC/HDMI"
#define         SUFFIX_NC_EURO "/sender/NC/EURO"
#define             SUFFIX_CMD "/sender/cmd"
#define      SUFFIX_CMD_RESULT "/sender/cmd/result"
#define         SUFFIX_RAWMODE "/sender/rawMode"
#define     SUFFIX_RAWMODE_VAL "/sender/rawMode/val"
#define   SUFFIX_SENDSTOREDRAW "/sender/sendStoredRaw"
#define SUFFIX_SENDSTORERAWSEQ "/sender/sendStoredRawSequence"

// ----------------------------------------------------------------
// Global includes
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "FS.h"
#include <IRremoteESP8266.h>      // https://github.com/markszabo/IRremoteESP8266 (use local copy)
#include <PubSubClient.h>         // https://github.com/knolleary/pubsubclient (id: 89)
#include <DNSServer.h>            // Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     // Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          // https://github.com/tzapu/WiFiManager WiFi Configuration Magic (id: 567)
#include <ArduinoJson.h>          // https://github.com/bblanchon/ArduinoJson (id: 64)

// Global variables
extern unsigned int rawIrData[SLOT_SIZE+1]; // RAW data storage
extern unsigned int rawSequence[SEQ_SIZE];
extern unsigned int rawIR1[SLOT_SIZE+1];
extern unsigned int rawIR2[SLOT_SIZE+1];
extern int rawIR1size, rawIR2size;
extern char mqtt_server[40];
extern char mqtt_user[32];
extern char mqtt_pass[32];
extern char mqtt_prefix[80];
extern bool buttonState; // State of control button
extern bool MQTTMode;
extern bool shouldSaveConfig ; //flag for saving data
extern String clientName; // MQTT client name
extern bool rawMode; // Raw mode receiver status
extern unsigned long lastAutoStart;
extern unsigned long autoStartFreq; // Frequency of autostart
extern bool autoStartSecond;
extern const bool useDebug;

// ------------------------------------------------
// Global objects

 extern IRrecv irrecv;
 extern IRsend irsend;
 extern WiFiClient wifiClient;
 extern PubSubClient client;

// ------------------------------------------------
// Functions declaration
unsigned long StrToUL(String inputString);
bool writeDataFile(const char* fName, unsigned int sourceArray[], int sourceSize);
int readDataFile(char * fName, unsigned int destinationArray[]);
String macToStr(const uint8_t* mac);
void saveConfigCallback ();
void loadDefaultIR();
void connect_to_MQTT();
void  encoding (decode_results *results, char * result_encoding);

void callback(char* topic, byte* payload, unsigned int length);
void connect_to_MQTT();
void loadDefaultIR();
void sendToDebug(String message);

#endif
