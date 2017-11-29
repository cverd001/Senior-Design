/*
 * Description: basic robotic car motion controlled by bluetooth 
 * Author: yidi
 * Created on Nov 10, 2017 10:47 pm
 */
#include <Arduino.h>
#include <Servo.h>
//******************* define motor pins *********************
const int motor_x1 = 12;      
const int motor_x2 = 13;
const int x_speed = 11;
const int motor_y1 = 7;
const int motor_y2 = 8;
const int y_speed = 10;
//**************** define ultrasonic pins *******************
const int ul_echo = 18;  // rx
const int ul_trig = 19; // tx
int Fspeedd = 0; // 前方距離
int Rspeedd = 0; // 右方距離
int Lspeedd = 0; // 左方距離
Servo myservo;
int servo_pin = 5;
//**************** define ultrasonic pins *******************
int move_direction = 1;
const int go_forward = 1; // 前進
const int go_right = 3; // 右轉
const int go_left = 4; // 左轉
const int go_back = 2; // 倒車
const int go_brake = 0;
//************** define light tracking pins ****************
//**********************************************************
//**********************************************************
int angle = 90;
int encoder_pinLeft = 2;  // The pin the encoder is connected
int encoder_pinRight = 3;  
int flag; 
int pulse_left = 0;
int pulse_right = 0;
// bluetooth command
char bluetooth_command;
char motion_control;

void setup()
{
    pinMode(motor_x1,OUTPUT);
    pinMode(motor_x2,OUTPUT);
    pinMode(x_speed,OUTPUT);
    pinMode(motor_y1,OUTPUT);
    pinMode(motor_y2,OUTPUT);
    pinMode(y_speed,OUTPUT);
    pinMode(ul_echo, INPUT); // 定義超音波輸入腳位
    pinMode(ul_trig, OUTPUT); // 定義超音波輸出腳位 
    pinMode(encoder_pinLeft, INPUT);
    pinMode(encoder_pinRight, INPUT);
    myservo.attach(servo_pin);
    attachInterrupt(0, encoder_counterLeft, FALLING);
    attachInterrupt(1, encoder_counterRight, FALLING);
    Serial.begin(9600);
}

void loop()
{
  pulse_left = 0;
  pulse_right = 0;
    angle = 20;
    //encoder_calculation();

    while(true){
      delay(20);
      if (pulse_left + pulse_right >100){
        break;
        }
      else
      {
        moveForward();
      }
    }
    brake();
    delay(2000);
 
    
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


