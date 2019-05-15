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

int motorL_F=4;
int motorL_B=5;
int motorL_speed=6;
int outMotorL;
int vel;

typedef struct pack Package;
Package data;
 
void setup(void)
{
   Serial.begin(115200);
   radio.begin();
   radio.openReadingPipe(1,pipe);
   radio.startListening();
   servo.attach(3);

   
   pinMode(motorL_F, OUTPUT);
   pinMode(motorL_B, OUTPUT);

}
 
void loop(void)
{
   if (radio.available())
   {
      radio.read(&data, sizeof data);
      delay(10);
      //Serial.println(data.X);
      Serial.println(data.Y);
      //Serial.println(data.servo);
      Serial.println(vel);
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

      vel = map(data.Y,30,224,-100,100);
      
      if(vel > 5){
        digitalWrite(motorL_F, HIGH);
        digitalWrite(motorL_B, LOW);
        //outMotorL = 255*data.X*0.01;
        outMotorL = map(vel,0,100,0,255);
        analogWrite(motorL_speed, outMotorL);
        Serial.println("Motor hacia delante");
        Serial.println(outMotorL);
      }else if(vel < -5){
        digitalWrite(motorL_F, LOW);
        digitalWrite(motorL_B, HIGH);
        //outMotorL = 255*(-data.X)*0.01;
        outMotorL = map(vel,-100,0,255,0);
        analogWrite(motorL_speed, outMotorL);
        Serial.println("Motor hacia atras");
        Serial.println(outMotorL);
      }else{
        digitalWrite(motorL_F, LOW);
        digitalWrite(motorL_B, LOW);
        analogWrite(motorL_speed, 0);
      }

      if(data.Z){
        digitalWrite(motorL_F, HIGH);
        digitalWrite(motorL_B, LOW);
        analogWrite(motorL_speed, 255);
      }

      if(data.C) {
        digitalWrite(motorL_F, LOW);
        digitalWrite(motorL_B, HIGH);
        analogWrite(motorL_speed,150 );
      }

      
   } 
   
}
