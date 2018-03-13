/*
 * Main_Motions
 * Description: this page includes pins, setup, and our main loop
 * 
 */
#include <Arduino.h>
#include <ADC.h>
#include "TeensyThreads.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <Wire.h>
//#include "LSM303.h"   //removed while not using compass

//----------Includes for IMU-----------------
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

//********************Teensy Pins*****************************
const int ledPin = 13;  //default embedded LED pin
//******************* Motor Pins *********************
const int motor_x1 = 11;  //digital motor pin A
const int motor_x2 = 12;  //digital motor pin B
const int x_speed = 14;   //analog write PWM pin
const int motor_y1 = 24;
const int motor_y2 = 25;
const int y_speed = 16;
const int motor_a1 = 27;     
const int motor_a2 = 28;
const int a_speed = 2;
const int motor_b1 = 7;
const int motor_b2 = 6;
const int b_speed = 29;

//************* define interrupt related pins **************
int encoder_pinLeft = 22;  //Encoder digital read
int encoder_pinRight = 23;
  
volatile int ticksL = 0;  //variable counter for encoder count reading
volatile int ticksR = 0;
//*************** define buzzer indicator *****************
const int buzzerPin = 17;
//************** define solar related pins ****************
int solarPin = 33;  //Solar Panel ADC reading
//*************** define photoresistor/solar pins***************
int photoR1Pin = 31;  //Left Photoresitors
int photoR2Pin = 32 ; //Right Photoresitors
//*******************IMU******************
int imuPin =39;   //interrupt pin
//SCL0=19   Clock Pin for IMU (default pins, dont need definition)
//SDA0=18   Data Pin for IMU
//*******************Raspberry Pi******************
int teensy2piPin = 8;
int pi2teensyPin =9;

float maxLightYaw = 0;    //optimal brightness heading
//********************Traverse Variables*************
int rows = 3;
int columns = 5; // grid dimensions
int menuFlag = 0; //for choosing menus, set in algMenu

/*
bool Calibrated = false;
int16_t initial_x = 0;
int16_t initial_y = 0;
int16_t initial_z = 0;
int compassCounter = 0;
LSM303 compass;
LSM303::vector<int16_t> running_min = {32767, 32767, 32767}, running_max = {-32768, -32768, -32768};
char report[80];
*/
//******************IMU**************************
MPU6050 mpu;
//#define OUTPUT_READABLE_EULER
#define OUTPUT_READABLE_YAWPITCHROLL

#define LED_PIN 13
bool blinkState=false;
// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

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

void ledBlink()   //1 blink, 2 seconds
{
    digitalWrite(ledPin, HIGH);   // set the LED on
    delay(1000);                  // wait for a second
    digitalWrite(ledPin, LOW);    // set the LED off
    delay(1000);                  // wait for a second
}

void ledSetupBlink()  //30 rapid blinks, 6 seconds
{
  int blinkcount  = 0;
   while( blinkcount < 30){
    digitalWrite(ledPin, HIGH);
    delay(100);
    digitalWrite(ledPin, LOW);
    delay(100);
    blinkcount = blinkcount +1;
   }
}

//---------------------------------------------------------------------------
void setup()
{
    delay(3000);
    Serial.println("Entered main_motions void setup()");
    //----------------------Unused Pins--------------------------
    // set unused I/O pins to Output mode to save power **UPDATE**
    pinMode(10,OUTPUT);
    pinMode(30,OUTPUT);  
    pinMode(21,OUTPUT);
    pinMode(20,OUTPUT);
    pinMode(15,OUTPUT);
    pinMode(34,OUTPUT);
//----------------------Pins We Use--------------------------------
    pinMode(teensy2piPin,OUTPUT);   //grey
    digitalWrite(teensy2piPin,LOW); //initialize off
    pinMode(pi2teensyPin,INPUT);    //white
    
    pinMode(ledPin,OUTPUT);   //teensy embedded LED
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
    
    pinMode(encoder_pinLeft, INPUT);
    pinMode(encoder_pinRight, INPUT);
    pinMode(buzzerPin, OUTPUT);
    
    pinMode(photoR1Pin,INPUT);  //photoresitor 1
    pinMode(photoR2Pin,INPUT);
    pinMode(solarPin,INPUT);  //solar panel adc

    /*
    adc->setAveraging(16); // set number of averages
    adc->setResolution(16); // set bits of resolution
    adc->setConversionSpeed(ADC_CONVERSION_SPEED::VERY_LOW_SPEED); // change the conversion speed
    adc->setSamplingSpeed(ADC_SAMPLING_SPEED::MED_SPEED); // change the sampling speed
    */
    attachInterrupt(encoder_pinLeft, encoderCounterLeft, CHANGE);
    attachInterrupt(encoder_pinRight, encoderCounterRight, CHANGE);

//---------------------IMU------------------------
 #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif
//-------------------------------    
    Serial.begin(115200);
    //while (!Serial);  //hopefully this isnt essential for IMU?
    ledSetupBlink();
    //scaleTone();
    //chirp();
    //Compass Stuff------------
    /*
    Wire.begin();
    compass.init();
    compass.enableDefault();
    */
//---------------------IMU Part 2------------------------
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();
  
    mpu.setXGyroOffset(-9);   //orignally 220  -9
    mpu.setYGyroOffset(-52);    //76             -52
    mpu.setZGyroOffset(15);   //-85            15
    mpu.setZAccelOffset(2130); // 1788          2130

      if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
        attachInterrupt(39, dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        // set our DMP Ready flag so the main loop() function knows it's okay to use it
        Serial.println(F("DMP ready! Waiting for first interrupt..."));
        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }
    //----------------------------------
    Serial.println("Exiting main_motions void setup()");    
    scaleFastTone();
} 

void loop(){
Tracking();
//printPhotoReadings();
 //readSolarVoltage();
 //algMenu();
//  laserTone();
//  scanPlus();

//scanPlus();
//laserTone();
//algMenu();
//spinImu();
//loadMenu();
//sizeMenu();
//Serial.println("entered for loop");
//  for(int i = 0; i <1100; i++) {
//    testIMU();
//    //Serial.println(i);
//  } 

//delay(200);
//chirp();  
//imuRight2(90);
//delay(3000);
//imuRight2(90);
//delay(3000);
//imuRight2(90);
//delay(3000);
//imuRight2(90);
//delay(3000);

//scanPlus();
//sizeMenu();
//traversePlus();
//delay(300);
//bootTone();
//Tracking();
//
//imuLeft(85);
//delay(2000);
//
//imuLeft(85);
//delay(2000);
//
//imuLeft(85);
//delay(2000);
//
//imuLeft(85);
//delay(2000);
//
//imuLeft(85);
//delay(2000);
//delay(2000);
//calMoveLeft(90);
//delay(1000);
//calMoveLeft(90);
//delay(2000);
//calMoveLeft(90);
//delay(2000);
//calMoveLeft(90);
//delay(1000);
//readSolarVoltage();
//Spin();
//Tracking();
//chirp();
//scan();
//moveRight()
//PerformTraverseAlg();

//  ledBlink();
  //chirp();
  //PerformTraverseAlg();
  //testIMU();
  //float inityaw;
  //float angle;
  //inityaw = calMoveRight(angle);
  //calMoving(inityaw, angle, 0);
  //calMoveLeft();
  //delay(1000);
}


