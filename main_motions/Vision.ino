//teensy tells pi when to start
//teensy moves 360 on imu
//rpi sends high digital output every time it sees a new max @angle
//teensy turns to best angle and moves forward until sensors read light

//teensy2piPin
//pi2teensyPin


void startScan(){
  digitalWrite(teensy2piPin,HIGH);  //start signal
}

void stopScan(){
  digitalWrite(teensy2piPin,LOW);  //start signal
}

void turnRightBurstImu(){
  int i = 0;
  int maxDegId = 0;
  float temp=0;
  Serial.println("Initializing IMU...");
  mpu.resetFIFO();
  for(int i = 0; i <175; i++) {
    testIMU();
  }
  Serial.println("Finished initializing IMU. Entering turning...");
  testIMU();
  float initYaw = ypr[0] * 180/M_PI + 180;

  for (i = 0; i < 36; i++){
    moveRight();
    while(true){
      testIMU();
      float currentYaw = ypr[0] * 180/M_PI + 180;
      if(initYaw+i*10>360){
        temp=initYaw+i*10-360;
        if(currentYaw>=temp){
          break;
        }
      }
      else{
        if(currentYaw >= initYaw+i*10){
          break;
        } 
      }   
    }
    brake();
    delay(500);
    if(digitalRead(pi2teensyPin)==HIGH){
      maxDegId=i;
    }
    delay(200);
  }

  //after finding max deg id
  stopScan();
  chirp();
  
  calMoveRight(maxDegId*10);
  victoryTone();
}

void headToLight(){
  moveForward();
  while(true){
    int lightness=readSolarVoltage();
    if (lightness >=120){
      break;
    }
  }
  brake();
  boopTone();
  delay(2000);
}

void scan(){
  startScan();
  turnRightBurstImu();  //finds best angle
  headToLight();        //goes to light
  Spin();
  victoryTone();
  Tracking(); //fix
}



