
///////////////////////ESPNOW DEFINITIONS///////////////////
#include <espnow.h> // Para ESP8266 sino seria esp_n
//#include <WiFi.h> // Para ESP32
#include <ESP8266WiFi.h> // para ESP8266

#define CHANNEL 0
////////////////////////////////////////////////////////////

////////////////////////ROVER IO AND FUNCTIONS//////////////
#include "Rover.h"
////////////////////////////////////////////////////////////

void OnMessageReceived( uint8_t* mac,  uint8_t* data, uint8_t len)
{
    
    memcpy(&joystick, data, sizeof(struct_message));
    
  Serial.println(joystick.forward);
}

// Init ESP Now with fallback
void InitESPNow() {
  
if(esp_now_init() != 0)

 {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  else
  {
    Serial.println("ESP NOW I OK");
  
    esp_now_register_recv_cb(OnDataRecv);
    Serial.println("ESP NOW II OK");
  
  }
  
}

/*
// config AP SSID
void configDeviceAP() {
  const char *SSID = "Slave_1";
  bool result = WiFi.softAP(SSID, "Slave_1_Password", CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
    Serial.print("AP CHANNEL "); Serial.println(WiFi.channel());
  }
}
*/
void setup() {
  //Serial.begin(115200);
   
  //Setup ESPNOW
  
  

  WiFi.mode(WIFI_STA);
 Serial.print("AP MAC: "); 
 Serial.println(WiFi.softAPmacAddress());
  // Init ESPNow with a fallback logic
  InitESPNow();
 

  //Setup IO for Rover´s Motors Control
  Rover_IO_Setup();
}

// callback when data is recv from Master
void OnDataRecv( uint8_t *mac_addr,  uint8_t *data, uint8_t data_len)
{
  //char macStr[18];
  //snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
          // mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);

  Serial.println("OnDataRecv I OK");
  
  memcpy(&joystick,data,data_len);
 Serial.println("OnDataRecv II OK");
 
  
  //Serial.print("Last Packet Recv from: "); Serial.println(macStr);
  Serial.print("Direction: "); Serial.println(joystick.forward);
  Serial.print("Sense: "); Serial.println(joystick.sense);
  
  Serial.println("");
  
}

void loop() {
  
   
  Serial.print("Direction: "); Serial.println(joystick.forward);
  Serial.print("Sense: "); Serial.println(joystick.sense);
  Serial.println("");
  
  avanti(joystick.forward,joystick.sense);
  
  //delay(200);
}
