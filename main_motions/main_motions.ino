/*
 * Description: basic robotic car motion controlled by bluetooth 
 * Author: yidi
 * Created on Nov 10, 2017 10:47 pm
 */
#include <Arduino.h>
#include <ADC.h>
#include "TeensyThreads.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
#include "LSM303.h"
//#include "Buzzer.ino"


//******************* define motor pins *********************
const int motor_x1 = 37;      
const int motor_x2 = 38;
const int x_speed = 14;
const int motor_y1 = 35;
const int motor_y2 = 36;
const int y_speed = 16;
const int motor_a1 = 28;//was pin4   
const int motor_a2 = 5;
const int a_speed = 2;
const int motor_b1 = 6;
const int motor_b2 = 7;
const int b_speed = 29;// was pin 3
//**********************************************************
const int ledPin = 13;
//************* define interrupt related pins **************
int encoder_pinLeft = 22;  // The pin the encoder is connected
int encoder_pinRight = 23;  
volatile int ticksL = 0;
volatile int ticksR = 0;
//*************** define buzzer indicator *****************
const int buzzerPin = 17;
//************** define solar related pins ****************
const int adc_read = 20;
ADC *adc = new ADC(); // adc object;
//*******************Compass******************
bool Calibrated = false;
int16_t initial_x = 0;
int16_t initial_y = 0;
int16_t initial_z = 0;
int compassCounter = 0;

LSM303 compass;
LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};

char report[80];


void encoderCounterLeft(){
  ticksL ++;
  //Serial.print("Left Encoder Ticks: ");
  //Serial.println(ticksL);
}

void encoderCounterRight(){
  ticksR ++;
  //Serial.print("Rightt Encoder Ticks: ");
  //Serial.println(ticksR);
}

void ledBlink()
{
    digitalWrite(ledPin, HIGH);   // set the LED on
    delay(1000);                  // wait for a second
    digitalWrite(ledPin, LOW);    // set the LED off
    delay(1000);                  // wait for a second
}

void ledSetupBlink()
{
  int blinkcount  = 0;
   while( blinkcount < 50){
    digitalWrite(ledPin, HIGH);   // set the LED on
    delay(100);                  // wait for a second
    digitalWrite(ledPin, LOW);    // set the LED off
    delay(100);                  // wait for a second

    blinkcount = blinkcount +1;
   }
}




void setup()
{
    delay(2000);
    Serial.println("Entered main_motions void setup()");
    //----------------------Unused Pins--------------------------
    // set unused I/O pins to Output mode to save power
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(12,OUTPUT);
    pinMode(24,OUTPUT);
    pinMode(25,OUTPUT);
    pinMode(26,OUTPUT);
    pinMode(27,OUTPUT);
    //pinMode(28,OUTPUT);motor  
    //pinMode(29,OUTPUT);motor
    pinMode(30,OUTPUT);
    pinMode(32,OUTPUT);
    
    pinMode(21,OUTPUT);
    pinMode(20,OUTPUT);
    //pinMode(19,OUTPUT); used for clock for compass
    //pinMode(18,OUTPUT); used for data for compass
    pinMode(15,OUTPUT);
    pinMode(13,OUTPUT);
    pinMode(33,OUTPUT);
    pinMode(34,OUTPUT);
//---------------------------------------------------
  
    pinMode(motor_x1,OUTPUT);
    pinMode(motor_x2,OUTPUT);
    pinMode(x_speed,OUTPUT);
    pinMode(motor_y1,OUTPUT);
    pinMode(motor_y2,OUTPUT);
    pinMode(y_speed,OUTPUT);
    
    pinMode(motor_a1,OUTPUT);
    pinMode(motor_a2,OUTPUT);
    pinMode(a_speed,OUTPUT);
    pinMode(motor_b1,OUTPUT);
    pinMode(motor_b2,OUTPUT);
    pinMode(b_speed,OUTPUT);
    
    pinMode(ledPin, OUTPUT);
    pinMode(encoder_pinLeft, INPUT);
    pinMode(encoder_pinRight, INPUT);
    pinMode(buzzerPin, OUTPUT);

    pinMode(adc_read, INPUT);
    adc->setAveraging(16); // set number of averages
    adc->setResolution(16); // set bits of resolution
    adc->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_LOW_SPEED); // change the conversion speed
    adc->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED); // change the sampling speed
    
    attachInterrupt(encoder_pinLeft, encoderCounterLeft, CHANGE);
    attachInterrupt(encoder_pinRight, encoderCounterRight, CHANGE);
    Serial.begin(9600);
    ledSetupBlink();
    chirp();
    //Compass Stuff------------
    Wire.begin();
    compass.init();
    compass.enableDefault();
    //----------------------------------
    Serial.println("Exiting main_motions void setup()");
} 


void loop()
{

//min: {  -297,   -647,   -291}    max: {  +396,    +46,   +445}

  
  while(true){
  calibrateCompassManual();
    //compass.m_min = (LSM303::vector<int16_t>){-297, -647, -291};
    //compass.m_max = (LSM303::vector<int16_t>){396, 46, 445};
  
 //heading();
  delay(20);
  }
  Serial.println("Entered main_motions void loop()");
  /*
  Serial.print("Initial x value: ");
  Serial.println(initial_x);
  Serial.print("Initial y value: ");
  Serial.println(initial_y);
  Serial.print("Initial z value: ");
  Serial.println(initial_z);
  */

  moveRightSlow();
  delay(60);
  compass.read();
  initial_x = compass.m.x;
  initial_y = compass.m.y;
  initial_z = compass.m.z;
  /*
  Serial.print("Initial x value: ");
  Serial.println(initial_x);/
  Serial.print("Initial y value: ");
  Serial.println(initial_y);
  Serial.print("Initial z value: ");
  Serial.println(initial_z);

  Serial.println("Entering Calibrate.calibrateCompass()");
  */
  while(Calibrated == false)
  {
    calibrateCompass();
  }

  heading();

    //delay(10000); 
    //Serial.println("Starting up");
    //moveForwardAdj(46);
    //bootTone();
    //PerformTraverseAlg();
    //turnRight(32); //correct for now
    //turnLeft(23); //correct for now
    //chirp(); 
}


