#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <Servo.h>
 
const int pinCE = 7;
const int pinCSN = 8;
RF24 radio(pinCE, pinCSN);
Servo servo;
 
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
struct pack{
  int Y = 0;
  int X = 0;
  int servo = 0; 
  boolean C = false;
  boolean Z = false;
};

typedef struct pack Package;
Package data;
 
void setup(void)
{
   Serial.begin(115200);
   radio.begin();
   radio.openReadingPipe(1,pipe);
   radio.startListening();
   servo.attach(3);
}
 
void loop(void)
{
   if (radio.available())
   {
      radio.read(&data, sizeof data);
      delay(10);
      Serial.println(data.X);
      Serial.println(data.Y);
      Serial.println(data.servo);
      if (data.C) {
        Serial.println("C -- Pulsado");
      } else {
        Serial.println("C -- No Pulsado");
      }

      if (data.Z) {
        Serial.println("Z -- Pulsado");
      } else {
        Serial.println("Z -- No Pulsado");
      }
   } 
   
}
