/*
* Arduino Wireless Communication Tutorial
*     Example 2 - Transmitter Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//#define led 12

float datos[3];

RF24 radio(7, 8); // CE, CSN

const byte addresses[][6] = {"00001", "00002"};
//boolean buttonState = 0;

void setup() {
  pinMode(12, OUTPUT);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
//  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  Serial.begin(9600);
}

void loop() {
  delay(5);
  datos[0]=analogRead(0)* (5.0 / 1023.0);;
  datos[1]=millis();
  datos[2]=3.14;
//  radio.stopListening();
  int potValue = analogRead(A0);
  int angleValue = map(potValue, 0, 1023, 0, 180);
  radio.write(&angleValue, sizeof(angleValue));
  bool ok = radio.write(datos, sizeof(datos));
  Serial.print(angleValue);
  if(ok){
    Serial.println("/t Enviado");
  }else{
    Serial.println("/t NO Enviado");
  }
  
/*  delay(5);
  radio.startListening();
  while (!radio.available());
  radio.read(&buttonState, sizeof(buttonState));
  if (buttonState == HIGH) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }*/
}
