/*
 * Description: basic robotic car motion controlled by bluetooth 
 * Author: yidi
 * Created on Nov 10, 2017 10:47 pm
 */
#include <Arduino.h>
#include <Servo.h>
#include "TeensyThreads.h"
//#include <car_basic_motions.ino>
//******************* define motor pins *********************

const int speed = 150;
int countMoves = 0;
int ticksR = 0;
int ticksL = 0;

const int motor_x1 = 37;      
const int motor_x2 = 38;
const int x_speed = 14;
const int motor_y1 = 35;
const int motor_y2 = 36;
const int y_speed = 16;
//
const int motor_a1 = 4;      
const int motor_a2 = 5;
const int a_speed = 2;
const int motor_b1 = 6;
const int motor_b2 = 7;
const int b_speed = 3;
//**************** define ultrasonic pins *******************
const int ul_echo = 18;  // rx
const int ul_trig = 19; // tx
int Fspeedd = 0; // 前方距離
int Rspeedd = 0; // 右方距離
int Lspeedd = 0; // 左方距離
Servo myservo;
//**************** define ultrasonic pins *******************
int move_direction = 1;
const int go_forward = 1; // 前進
const int go_right = 3; // 右轉
const int go_left = 4; // 左轉
const int go_back = 2; // 倒車
const int go_brake = 0;
//************** define light tracking pins ****************
const int light_a0 = 17;
int light_value = 0;
//**********************************************************
const int ledPin = 13;
//**********************************************************
int angle = 90;
int encoder_pinLeft = 22;  // The pin the encoder is connected
int encoder_pinRight = 23;  
int flag; 
int pulse_left = 0;
int pulse_right = 0;
// bluetooth command
char bluetooth_command;
char motion_control;

const int buzzerPin = 17;



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
    Serial.begin(9600);
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
    
    pinMode(ul_echo, INPUT); // 定義超音波輸入腳位
    pinMode(ul_trig, OUTPUT); // 定義超音波輸出腳位 
    pinMode(ledPin, OUTPUT);
    pinMode(encoder_pinLeft, INPUT);
    pinMode(encoder_pinRight, INPUT);
    pinMode(buzzerPin, OUTPUT);
    

    ledSetupBlink();
    chirp();
    Serial.print("Speed: ");
    Serial.println(speed);
    Serial.println("------------------------------------------------------");
}


void loop()
{
  while(true)
  {
    moveForwardAdj2(60);
    //turn(90);
    //chirp();
    delay(6000);
  }  
   // moveForwardAdj(50);
    //delay(2000);
    //moveForwardAdj(10);
    //delay(2000);
    
    //moveLeft();
    //delay(2000);
    //moveBack();
    //delay(2000);
    //moveRight();
    //delay(2000);
    //angle = 120;
    //encoder_calculation();
//    lightTracking();
//    ultrasonicDetection(); //測量角度 並且判斷要往哪一方向移動
//    switch(move_direction)
//    {
//        case 1: moveForward(100); break;
//        case 2: moveBack(100); break;
//        case 3: moveRight(100); break;
//        case 4: moveLeft(100); break;
//        case 0: brake(100); break; 
//    }    
}


