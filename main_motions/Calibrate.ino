#include <Wire.h>
#include "LSM303.h"


void calibrateCompassManual() {  
  compass.read();
 
  running_min.x = min(running_min.x, compass.m.x);
  running_min.y = min(running_min.y, compass.m.y);
  running_min.z = min(running_min.z, compass.m.z);

  running_max.x = max(running_max.x, compass.m.x);
  running_max.y = max(running_max.y, compass.m.y);
  running_max.z = max(running_max.z, compass.m.z);
  
  snprintf(report, sizeof(report), "min: {%+6d, %+6d, %+6d}    max: {%+6d, %+6d, %+6d}",
    running_min.x, running_min.y, running_min.z,
    running_max.x, running_max.y, running_max.z);
  compassCounter = compassCounter +1;
  Serial.print("Compass counter: ");
  Serial.println(compassCounter);
  
  Serial.println(report);
  
  Serial.print("Compass counter: ");
  Serial.println(compassCounter);

  Serial.print("Current x value = ");
  Serial.println(compass.m.x);
  Serial.print("Current y value = ");
  Serial.println(compass.m.y);  
  Serial.print("Current z value = ");
  Serial.println(compass.m.z);


  delay(10);   //initially 100

}








void calibrateCompass() {  
  compass.read();
 
  running_min.x = min(running_min.x, compass.m.x);
  running_min.y = min(running_min.y, compass.m.y);
  running_min.z = min(running_min.z, compass.m.z);

  running_max.x = max(running_max.x, compass.m.x);
  running_max.y = max(running_max.y, compass.m.y);
  running_max.z = max(running_max.z, compass.m.z);
  
  snprintf(report, sizeof(report), "min: {%+6d, %+6d, %+6d}    max: {%+6d, %+6d, %+6d}",
    running_min.x, running_min.y, running_min.z,
    running_max.x, running_max.y, running_max.z);
  compassCounter = compassCounter +1;
  Serial.print("Compass counter: ");
  Serial.println(compassCounter);
/*
  Serial.print("Compass counter: ");
  Serial.println(compassCounter);
  

  Serial.println(report);
  
  Serial.print("Compass counter: ");
  Serial.println(compassCounter);

  Serial.print("Current x value = ");
  Serial.println(compass.m.x);
  Serial.print("Current y value = ");
  Serial.println(compass.m.y);  
  Serial.print("Current z value = ");
  Serial.println(compass.m.z);
*/

  delay(5);   //initially 100

  if(
  (compass.m.x >= initial_x -35) && (compass.m.x <= initial_x + 35) &&
  (compass.m.y >= initial_y -35) && (compass.m.y <= initial_y + 35) &&
//  (compass.m.z >= initial_z -15) && (compass.m.z <= initial_z + 15) &&  
  (compassCounter > 150)
    )
  {
    brake();
    Calibrated = true;  
    compass.m_min = (LSM303::vector<int16_t>){running_min.x, -running_min.y, -running_min.z};
    compass.m_max = (LSM303::vector<int16_t>){running_max.x, running_max.y, running_max.z};
    
    Serial.println("Exiting Calibrate.calibrateCompass()");
  }
}



//----------------------------------------------------------------------------------




//LSM303 compass;
//
//  
//  /*
//  Calibration values; the default values of +/-32767 for each axis
//  lead to an assumed magnetometer bias of 0. Use the Calibrate example
//  program to determine appropriate values for your particular unit.
//  */
//  compass.m_min = (LSM303::vector<int16_t>){-36, -1318, -525};
//  compass.m_max = (LSM303::vector<int16_t>){163, -1199, -448};
//
//void loop() {
//  delay(100);
//  compass.read();
//  
//  /*
//  When given no arguments, the heading() function returns the angular
//  difference in the horizontal plane between a default vector and
//  north, in degrees.
//  
//  The default vector is chosen by the library to point along the
//  surface of the PCB, in the direction of the top of the text on the
//  silkscreen. This is the +X axis on the Pololu LSM303D carrier and
//  the -Y axis on the Pololu LSM303DLHC, LSM303DLM, and LSM303DLH
//  carriers.
//  
//  To use a different vector as a reference, use the version of heading()
//  that takes a vector argument; for example, use
//  
//    compass.heading((LSM303::vector<int>){0, 0, 1});
//  
//  to use the +Z axis as a reference.
//  */
//  float heading = compass.heading();
//  
//  Serial.println(heading);
//  delay(100);
//}

void heading()
{
  while(true){
  delay(100);
  compass.read(); 
  float heading = compass.heading();
  
  Serial.println(heading);
  //delay(100);
  }
}
void headingTest()
{
  while(true){
    delay(100);
    compass.read();
    float heading = compass.heading();
    brake();
    //if(heading

    moveRight();
    delay(500);
    brake();
  }

}

