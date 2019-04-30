/*
 * If you use the serial monitor for debugging remember to ster the baud rate to 115200.
 * The modules are set to only one-way communication. That means that the controller can only transmit and the tank can only receive.
 * If you wish to change this for two-way communication there is plenty of documentation to do so on the internet and in examples.
 * 
 * This program reads the analog input of the joystick and sends it in packets to te tank.
 */
#include <SPI.h>  
#include "RF24.h"

RF24 myRadio (7, 8);
byte addresses[][6] = {"0"};

struct package
{
  int X=1;
  int Y=1;
  int Z=1;
  int W=1;
  int B = 0;
};


typedef struct package Package;
Package data;


void setup()
{
  Serial.begin(115200);
  delay(100);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openWritingPipe( addresses[0]);
  delay(100);
  pinMode(2, INPUT);
}

void loop()
{
 
  

  Serial.print("X:");
  Serial.print(data.X);
  Serial.print("    Y");
  Serial.println(data.Y);
  Serial.print("    Z");
  Serial.println(data.Z);
  Serial.print("    W");
  Serial.println(data.W);
  Serial.print("    B");
  if (data.B == 1) {
    Serial.println("1");
  } else {
    Serial.println("0");
  }
  data.X = analogRead(A0);
  data.Y = analogRead(A1);
  data.Z = analogRead(A2);
  data.W = analogRead(A3);
  data.B = digitalRead(2);

  myRadio.write(&data, sizeof(data)); 
  
  delay(100);
}
