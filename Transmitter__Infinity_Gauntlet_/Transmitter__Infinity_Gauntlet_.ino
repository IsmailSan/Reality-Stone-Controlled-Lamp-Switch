
#include <SPI.h>        //SPI library for communicate with the nRF24L01+
#include "RF24.h"       //The main library of the nRF24L01+
#include "Wire.h"       //For communication
#include "I2Cdev.h"     //For communicate with MPU6050
#include "MPU6050.h"    //The main library of the MPU6050
#include <FastLED.h>

#define LED_PIN     10
#define NUM_LEDS    6

CRGB leds[NUM_LEDS];


//Define the object to access and cotrol the Gyro and Accelerometer (We don't use the Gyro data)
MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

//Define packet for the direction (X axis and Y axis)
int data1;
int data2;

boolean t= false;

//Define object from RF24 library - 7 and 8 are a digital pin numbers to which signals CE and CSN are connected.
RF24 radio(7,8);

//Create a pipe addresses for  communication                                    
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup(){
  
FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
Serial.begin(9600);
Wire.begin();
Serial.println(mpu.testConnection() ? "Connected" : "Connection failed");
mpu.initialize();              //Initialize the MPU object
radio.begin();                 //Start the nRF24 communicate     
radio.openWritingPipe(pipe);   //Sets the address of the receiver to which the program will send data.
}

void loop(){
  
//With this function, the acceleration and gyro values of the axes are taken. 
mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

 //In two-way control, the X axis (data [0]) of the MPU6050 allows the robot to move forward and backward. 
 //Y axis (data [0]) allows the robot to right and left turn.
data1 = map(ax,-17000 , 17000, 0, 400 ); //Send X axis data 


Serial.println(data1); 
delay(200); 


if(data1 > 340){
  t=!t;
  delay(1000);
}
if(t==true) {
  leds[2] = CRGB(255, 0, 0);
} else {
leds[2] = CRGB(0, 0, 0);
}
FastLED.show();

radio.write(&data1, sizeof(data1));
  
  

}
