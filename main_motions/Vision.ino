//teensy tells pi when to start
//teensy moves 360 on imu
//rpi sends high digital output every time it sees a new max @angle
//teensy turns to best angle and moves forward until sensors read light

//teensy2piPin
//pi2teensyPin

void startScan(){
  teensy2piPin = HIGH;  //start signal
}

void scan(){
  calMoveRightScan(360);  //set maxLightYaw
  return2MaxLight(maxLightYaw);
  teensy2piPin=LOW;     //end signal
}



