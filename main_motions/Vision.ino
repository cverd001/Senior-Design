//teensy tells pi when to start
//teensy moves 360 on imu
//rpi sends high digital output every time it sees a new max @angle
//teensy turns to best angle and moves forward until sensors read light

//teensy2piPin
//pi2teensyPin


void startScan(){
  digitalWrite(teensy2piPin,HIGH);  //start signal
  laserTone();
  Serial.println("Sending start signal to pi");
}

void stopScan(){
  digitalWrite(teensy2piPin,LOW);  //start signal
  Serial.println("Sending stop signal to pi");
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



void turnRightBurstImu(){
  int i = 0;
  int maxDegId = 0;
  float temp=0;
  Serial.println("Initializing IMU...");
  mpu.resetFIFO();
  for(int i = 0; i <175; i++) {
    testIMU();
  }
  testIMU();
  float initYaw = ypr[0] * 180/M_PI + 180;
  Serial.println("Finished initializing IMU. Entering turning...");
  for (i = 0; i < 36; i++){  
    calMoveRight(20);
    Serial.print("Right turn number: ");
    Serial.println(i);
    if(digitalRead(pi2teensyPin)==HIGH){
      bootTone();
      maxDegId=i;
      Serial.print("Raspberry Pi sent HIGH signal! New max set to ");
      Serial.println(i);
    }
  }
  Serial.println("Done with right turns!");
}


void scan(){
  laserTone();
  startScan();
  turnRightBurstImu();  //finds best angle
  delay(30000);
  //headToLight();        //goes to light
  //Spin();
  victoryTone();
  Tracking(); //fix
}

void scanPlus(){
  for(int i = 0; i <1100; i++) {
    testIMU();
    Serial.println(i);
  }
  scaleTone();
  scan();

}

