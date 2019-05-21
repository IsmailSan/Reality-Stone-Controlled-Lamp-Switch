
#include <SPI.h>      //SPI library for communication with the nRF24L01+
#include "RF24.h"  //The main library of the nRF24L01+
#include <Servo.h> // servo library


RF24 radio (7,8); // CE,CSN
Servo myServo;
Servo myServoo;

//Define packet for the direction (X axis and Y axis)
int data1;

boolean t= false;


//Create a pipe addresses for  communication
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
Serial.begin(9600);
myServo.attach(5);
myServoo.attach(4);
radio.begin();                    //Start the nRF24 communicate            
radio.openReadingPipe(1, pipe);   //Sets the address of the transmitter to which the program will receive data.
radio.startListening();         

}

void loop() {
  if (radio.available()) {
    radio.read(&data1, sizeof(data1));
    Serial.println(data1); 
  }
  
if(data1 > 340){
t=!t;
delay(1000);
  
}
if(t==true) {
 myServo.write(180); 
 myServoo.write(30);
 
}else {
 myServoo.write(0);
 myServo.write(130);
   }

}


