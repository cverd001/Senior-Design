#include <Arduino.h>
#include <ADC.h>
#include "TeensyThreads.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>


const int ledPin = 13;
void ledBlink()
{
    digitalWrite(ledPin, HIGH);   // set the LED on
    delay(1000);                  // wait for a second
    digitalWrite(ledPin, LOW);    // set the LED off
    delay(1000);                  // wait for a second
}


/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void setup() 
{
  ledBlink(); 
  Serial.begin(9600);
  Serial.println("Magnetometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  else
  {
    Serial.println("test");
  }
}
void loop() 
{
   Serial.println("test");
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
  
  float Pi = 3.14159;
  
  // Calculate the angle of the vector y,x
  float heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
  
  // Normalize to 0-360
  if (heading < 0)
  {
    heading = 360 + heading;
  }
  Serial.print("Compass Heading: ");
  Serial.println(heading);
  delay(500);
}
