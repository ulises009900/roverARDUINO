#include <esp_now.h>
#include <WiFi.h>
#include "const.h"

const int pinX = 35;
const int pinY = 34;
const int pinSW = 23;

struct_message joystick = {115, 115, 0};  // Inicialización por defecto

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t* mac_addr, esp_now_send_status_t status) {
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "envio exitoso" : "envio fallado");
}

void RegisterPeeks() {
  memcpy(peerInfo.peer_addr, MAC_RECEIVER_1, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
  } else {
    Serial.println("Registered peer");
  }
}

void InitEspNow() {
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
  } else {
    esp_now_register_send_cb(OnDataSent);
    RegisterPeeks();
  }
}

void SendMessage() {
  esp_err_t result = esp_now_send(MAC_RECEIVER_1, (uint8_t*)&joystick, sizeof(struct_message));
  if (result == ESP_OK) {
    Serial.println("enviado con exito");
  } else {
    Serial.println("Error enviando la data");
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000);

  WiFi.mode(WIFI_STA);
  InitEspNow();

  analogReadResolution(12); // Para valores de 0 a 4095
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);
  
}

void loop() {
  int valorX = analogRead(pinX);
  int valorY = analogRead(pinY);

  joystick.avanzar = map(valorY, 0, 4095, 0, 250); // Movimiento adelante/atrás
  joystick.sense = map(valorX, 0, 4095, 0, 250);   // Movimiento lateral
  joystick.rotate = 0; 

  Serial.print("avanzar: ");
  Serial.print(joystick.avanzar);
  Serial.print(" | Sense: ");
  Serial.println(joystick.sense);

  SendMessage();
  delay(200); // Envío cada 200 ms
}
