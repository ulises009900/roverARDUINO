#define IN1 5   //GPIO14
#define IN2 4   //GPIO27
#define IN3 12   //GPIO25 
#define IN4 14   //GPIO33 
#define ENA 0   //GPIO12 
#define ENB 13   //GPIO32 

// uno de los esp8266 tiene MAC  48:55:19:e0:67:76

const uint8_t MAC_SENDER_1[] = { 0x08, 0x3A, 0xF2, 0x6E, 0x10, 0xC4 };

// data Structure from Joystick
typedef struct struct_message {
     int forward = 5; //0 retro max vel. 250 forward max vel. 
     int sense = 5; //250 dx max vel 0 sx max vel.
     int rotate=0;
     
} struct_message;

struct_message joystick;

void avanti(int dir, int sense);
void avanti (int dir, int sense)
{
  int dx=0;
  int sx=0;

  if(sense>110 && sense<120)
  {
    dx=0;
    sx=0;
  } 
  else if(sense<110)
       {
          dx=0;
          sx=map(sense,110,0,100,200);
       }
       else
       {
          sx=0;
          dx=map(sense,120,255,100,200);
       }
       
    
  if(dir>120)
  {
    analogWrite(ENA,map(dir,120,255,0,255)-dx);
    analogWrite(ENB,map(dir,120,255,0,255)-sx);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
  }
  
  if(dir < 110)
  {
    analogWrite(ENA,map(dir,110,0,0,255)-dx);
    analogWrite(ENB,map(dir,110,0,0,255)-sx);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }
  
  if(dir <120 && dir >110)
  {
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
}

void Rover_IO_Setup();
void Rover_IO_Setup() 
{
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT); 
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT); 
  
  digitalWrite(ENA,LOW);
  digitalWrite(ENB,LOW);
  
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
