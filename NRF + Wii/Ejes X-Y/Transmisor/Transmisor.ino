#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <Wiichuck.h>
#include <Wire.h>
 
const int pinCE = 7;
const int pinCSN = 8;
RF24 radio(pinCE, pinCSN);
Wiichuck wii;

struct pack{
  int Y = 0;
  int X = 0;
  boolean C = false;
  boolean Z = false;
};
 
// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;
 
//char data[16]="Hola mundo" ;

typedef struct pack Package;
Package data;
 
void setup(void)
{
   radio.begin();
   radio.openWritingPipe(pipe);
   wii.init();

   wii.calibrate(); 
}
 
void loop(void)
{  

	if (wii.poll()) {
//	data.Y = map(wii.joyY(), 33, 222, -100, 100);
//	data.X = map(wii.joyX(), 15, 214, -100, 100);
//	data.servo = map(wii.accelX(), 140, 90, 0, 45);

 		data.Y = wii.joyY();
		data.X = wii.joyX();

 		data.C = wii.buttonC();
 		data.Z = wii.buttonZ();

		radio.write(&data, sizeof data);
		delay(10);
	}
   
}
