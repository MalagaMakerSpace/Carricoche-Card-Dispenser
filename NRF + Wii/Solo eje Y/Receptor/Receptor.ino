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
  boolean C = false;
  boolean Z = false;
};

int motorL_F=4;
int motorL_B=5;
int motorL_speed=6;

int motorR_F=10;
int motorR_B=11;
int motorR_speed=12;

int outMotorL;
int outMotorR;
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

   pinMode(motorR_F, OUTPUT);
   pinMode(motorR_B, OUTPUT);

}
 
void loop(void)
{
   if (radio.available())
   {
      radio.read(&data, sizeof data);
      delay(10);
      //Serial.println(data.X);
      Serial.println(data.Y);
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

        digitalWrite(motorR_F, HIGH);
        digitalWrite(motorR_B, LOW);

        outMotorL = map(vel,0,100,0,255);
        analogWrite(motorL_speed, outMotorL);
        analogWrite(motorR_speed, outMotorL);

        Serial.println("Motores hacia delante");
        Serial.println(outMotorL);
        Serial.println(outMotorR);
      }else if(vel < -5){
        digitalWrite(motorL_F, LOW);
        digitalWrite(motorL_B, HIGH);

        digitalWrite(motorR_F, LOW);
        digitalWrite(motorR_B, HIGH);

        outMotorL = map(vel,-100,0,255,0);
        analogWrite(motorL_speed, outMotorL);
        analogWrite(motorR_speed, outMotorL);

        Serial.println("Motores hacia atras");
        Serial.println(outMotorL);
      }else{
        digitalWrite(motorL_F, LOW);
        digitalWrite(motorL_B, LOW);
        digitalWrite(motorR_F, LOW);
        digitalWrite(motorR_B, LOW);

        analogWrite(motorL_speed, 0);
        analogWrite(motorR_speed, 0);
      }

      if(data.Z){
        digitalWrite(motorL_F, HIGH);
        digitalWrite(motorL_B, LOW);
        analogWrite(motorL_speed, 255);
      }

      if(data.C){
        digitalWrite(motorR_F, HIGH);
        digitalWrite(motorR_B, LOW);
        analogWrite(motorL_speed, 255);
      }

   } 
   
}
