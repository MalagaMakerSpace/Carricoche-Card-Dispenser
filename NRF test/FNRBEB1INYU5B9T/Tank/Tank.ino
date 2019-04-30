/*
 * If you use the serial monitor for debugging remember to ster the baud rate to 115200.
 * The modules are set to only one-way communication. That means that the controller can only transmit and the tank can only receive.
 * If you wish to change this for two-way communication there is plenty of documentation to do so on the internet and in examples.
 * 
 * This program receives the X and Y values and processes it into movement.
 */
#include <SPI.h>  
#include "RF24.h"
#include <Servo.h> 

RF24 myRadio (7, 8); 
struct package
{
  int X=512;
  int Y=512;
  int Z=512;
  int W=512;
  int B=0;
};

byte addresses[][6] = {"0"}; 


typedef struct package Package;
Package data;

Servo myServo;
int angleV = 0;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  myServo.attach(5);
  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{
  if ( myRadio.available()) 
  {
      myRadio.read( &data, sizeof(data) );
    Serial.print("X:");
    Serial.print(data.X);
    Serial.print("      Y");
    Serial.println(data.Y);
    Serial.print("      Z");
    Serial.println(data.Z);
    Serial.print("      W");
    Serial.println(data.W);
    Serial.print("      B");
    Serial.println(data.B);
    
 /*   int X = data.X;
    int Y = data.Y;
    int Z = data.Z;
    int W = data.W;
    int B = data.B;
    
    myRadio.read(&angleV, sizeof(angleV));
     myServo.write(angleV);
 */ 
    
  } else {
    Serial.println("Not Connected");
  }

}
