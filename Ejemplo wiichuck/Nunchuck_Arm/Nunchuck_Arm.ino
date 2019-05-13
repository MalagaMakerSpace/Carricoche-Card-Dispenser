#include <Wiichuck.h>
#include <Wire.h>

Wiichuck wii;

//The motor from the base that moves the arm right-left
int Base1_1 = 3;
int Base1_2 = 4;
//The motor from the base that moves the arm up-down
int Base2_1 = 5;
int Base2_2 = 6;
//The first join counting from the base to the grip
int Join1_1 = 7;
int Join1_2 = 8;
//The second join counting from the base to the grip
int Join2_1 = 9;
int Join2_2 = 10;
//The grip
int Grip1 = 11;
int Grip2 = 12;
//The led from the grip and if it is on off
int Led = 13;
bool state = false;

void setup() {
  Serial.begin(9600);
  wii.init();

  // Set all the motor control pins to outputs
  pinMode(Base1_1, OUTPUT);
  pinMode(Base1_2, OUTPUT);
  pinMode(Base2_1, OUTPUT);
  pinMode(Base2_2, OUTPUT);
  pinMode(Join1_1, OUTPUT);
  pinMode(Join1_2, OUTPUT);
  pinMode(Join2_1, OUTPUT);
  pinMode(Join2_2, OUTPUT);
  pinMode(Grip1, OUTPUT);
  pinMode(Grip2, OUTPUT);
  pinMode(Led, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(Base1_1, LOW);
  digitalWrite(Base1_2, LOW);
  digitalWrite(Base2_1, LOW);
  digitalWrite(Base2_2, LOW);
  digitalWrite(Join1_1, LOW);
  digitalWrite(Join1_2, LOW);
  digitalWrite(Join2_1, LOW);
  digitalWrite(Join2_2, LOW);
  digitalWrite(Grip1, LOW);
  digitalWrite(Grip2, LOW);
  digitalWrite(Led, LOW);
  
  wii.calibrate();  // calibration
}


void loop() {
  
  if (wii.poll()) {

    if(wii.joyX()>150 && !wii.buttonC()){
      digitalWrite(Base1_1, HIGH);
      digitalWrite(Base1_2, LOW);
    }else if(wii.joyX()<100 && !wii.buttonC()){
      digitalWrite(Base1_1, LOW);
      digitalWrite(Base1_2, HIGH);
    }else{
      digitalWrite(Base1_1, LOW);
      digitalWrite(Base1_2, LOW);
    }

    if(wii.joyY()>150 && !wii.buttonC()){
      digitalWrite(Base2_1, HIGH);
      digitalWrite(Base2_2, LOW);
    }else if(wii.joyY()<100 && !wii.buttonC()){
      digitalWrite(Base2_1, LOW);
      digitalWrite(Base2_2, HIGH);
    }else{
      digitalWrite(Base2_1, LOW);
      digitalWrite(Base2_2, LOW);
    }

    if(wii.accelY()>600){
      digitalWrite(Join1_1, HIGH);
      digitalWrite(Join1_2, LOW);
    }else if(wii.accelY()<400){
      digitalWrite(Join1_1, LOW);
      digitalWrite(Join1_2, HIGH);
    }else{
      digitalWrite(Join1_1, LOW);
      digitalWrite(Join1_2, LOW);
    }

    if(wii.joyY()>150 && wii.buttonC()){
      digitalWrite(Join2_1, HIGH);
      digitalWrite(Join2_2, LOW);
    }else if(wii.joyY()<100 && wii.buttonC()){
      digitalWrite(Join2_1, LOW);
      digitalWrite(Join2_2, HIGH);
    }else{
      digitalWrite(Join2_1, LOW);
      digitalWrite(Join2_2, LOW);
    }

    if(wii.joyX()>150 && wii.buttonC()){
      digitalWrite(Grip1, HIGH);
      digitalWrite(Grip2, LOW);
    }else if(wii.joyX()<100 && wii.buttonC()){
      digitalWrite(Grip1, LOW);
      digitalWrite(Grip2, HIGH);
    }else{
      digitalWrite(Grip1, LOW);
      digitalWrite(Grip2, LOW);
    }

    if(wii.buttonZ()){
      //state!=state;
      //if(state){
        digitalWrite(Led,HIGH);
      //}else{
      //  digitalWrite(Led,LOW);
      //}
    }else{
      digitalWrite(Led,LOW);
    }

    
    
    Serial.print("joy:");
    Serial.print(wii.joyX());
    Serial.print(", ");
    Serial.print (wii.joyY());
    Serial.print("  \t");
    
    Serial.print("accle:");
    Serial.print(wii.accelX());
    Serial.print(", ");
    Serial.print(wii.accelY());
    Serial.print(", ");
    Serial.print(wii.accelZ());
    Serial.print("  \t");
    Serial.print("button:");
    Serial.print(wii.buttonC());
    Serial.print(", ");
    Serial.print(wii.buttonZ());
    Serial.println();
    
  }
  

}
