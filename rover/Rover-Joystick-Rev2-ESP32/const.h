#include <Arduino.h>

// Dirección MAC del receptor
const uint8_t MAC_RECEIVER_1[] = { 0x48 ,0x55 ,0x19 ,0xe0 ,0x67, 0x76 };

// Estructura de mensaje
typedef struct struct_message {
  int avanzar;
  int sense;
  int rotate;
} struct_message;
