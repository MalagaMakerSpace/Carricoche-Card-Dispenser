#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
 
const int pinCE = 7;
const int pinCSN = 8;
RF24 radio(pinCE, pinCSN);

struct pack{
  int Y=0;
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
}
 
void loop(void)
{
   data.Y=analogRead(A0);
   radio.write(&data, sizeof data);
   delay(10);
}
