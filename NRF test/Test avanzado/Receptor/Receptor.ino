#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <Servo.h>
 
const int pinCE = 7;
const int pinCSN = 8;
RF24 radio(pinCE, pinCSN);
Servo servoX;
Servo servoY;
 
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
struct pack {

  int X = 0;
  int Y = 0;
  boolean B = false;
  
};

typedef struct pack Package;
Package data;
 
void setup(void)
{
   Serial.begin(115200);
   radio.begin();
   radio.openReadingPipe(1,pipe);
   radio.startListening();
   servoX.attach(3);
   servoY.attach(4);
}
 
void loop(void)
{
   if (radio.available())
   {
      /*int done =*/ radio.read(&data, sizeof data);
      delay(10);
      data.Y = map(data.Y,0,1023,0,180);
      data.X = map(data.X,0,1023,-180,180);
      servoY.write(data.Y);
      servoX.write(data.X);
      Serial.println(data.Y);
      Serial.println(data.X);
      if (data.B) {
        Serial.println("Pulsado");
      } else {
        Serial.println("No Pulsado");
      }
   } 
   
}
