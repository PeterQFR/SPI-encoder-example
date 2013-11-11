/**
SPI_encoder_talk.pde
Author: Peter Milani
Company: Queensland Field Robotics
Licence: BSD - open use, no warranty
*/

#include <SPI.h>
#include <inttypes.h>

int CSn;
uint8_t readbuf[2];
void setup() 
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //initialise spi communications as 1MHz
  CSn =9;
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.setDataMode(SPI_MODE1);
  pinMode(CSn, OUTPUT);
  digitalWrite(CSn, HIGH);
  
}


void loop() 

{
  //To Read the angle of the sensor we must send a read command for
  //the appropriate register which for angles is x3FFF
  
  //so to read from this register we must send 0b1111 0111 1111 1111
  
  
  //this transfer will consist of two spi bytes each of 0xFF
  digitalWrite(CSn, LOW);
  
  
  uint8_t val = 0xFF;
  SPI.transfer(val);

  
  //Read in values
  SPI.transfer(val);
    
  //After 16 clock cycles Csn must be pulled high to reset some parts
  //of the interface core
  digitalWrite(CSn, HIGH);
  digitalWrite(CSn,LOW);
  
  //Now send a NOP 0b0000 0000 0000 0000and recieve the latest angle
  val = 0x00;
  readbuf[0]=SPI.transfer(val);
   
  
  val = 0x00;
  readbuf[1] = SPI.transfer(val);
  
  digitalWrite(9, HIGH);
  //Break down readbuf into its integer representation:
  
  uint16_t angle = readbuf[0]&0b00111111;
   angle = angle << 8;
   angle = angle + readbuf[1];
   //angle = 1000;
  // print out the value you read:
 
  
  Serial.println(angle);
  delay(1500);        // delay in between reads for stability
}
