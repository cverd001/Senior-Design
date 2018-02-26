
void calMoveRight(float angle){
  angle = angle - 10;
  mpu.resetFIFO();
  for(int i = 0; i <175; i++) {
  	testIMU();
  }
  Serial.println("Initializing IMU...");
  Serial.println("Finished initializing IMU. Entering turning...");
  testIMU();
  float inityaw = ypr[0] * 180/M_PI + 180;
  Serial.print("Initial yaw: ");
  Serial.println(inityaw);
  float calyaw;
  float temp = inityaw + angle;
  if (temp > 360)
    temp = temp - 360;
  moveRight();
  while (true) {
    testIMU();
    calyaw = ypr[0] * 180/M_PI + 180;
    if(temp < angle && calyaw > 360 - angle) {
      calyaw = calyaw - 360;
    }
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw >= temp){
      break;
    }
  }
  brake();
  delay(300);
}

void calMoveLeft(float angle) {
  angle = angle - 10;
  mpu.resetFIFO();
  Serial.println("Initializing IMU...");
  for(int i = 0; i < 175; i++) {
  	testIMU();
  }
  Serial.println("Finished initializing IMU. Entering turning...");
  testIMU();
  float inityaw = ypr[0] * 180/M_PI + 180;
  Serial.print("Initial yaw: ");
  Serial.println(inityaw);
  float calyaw = inityaw;
  float temp = inityaw - angle;
  if (temp < 0)
    temp = temp + 360;
  moveLeft(); 
  while (true) {
    testIMU();
    calyaw = ypr[0] * 180/M_PI + 180;
    if(temp >= 360 - angle && calyaw <= angle) {
      testIMU();
      calyaw = ypr[0] * 180/M_PI + 180;
      calyaw = calyaw + 360;
    }
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw <= temp)
      break;
  }
  brake();
  delay(300);
}

void calMoving(float inityaw, float angle, bool tDirection) {
  mpu.resetFIFO();
  testIMU();
  float curryaw = ypr[0] * 180/M_PI + 180;
  float idlyaw;                                     // ideal yaw after turning
  float err; 
  float tol = 5;
  if(tDirection == 0) {                            // turned right 
    idlyaw = inityaw + angle;
    idlyaw = (idlyaw < 360)?idlyaw:(idlyaw - 360);
    err = curryaw - idlyaw;                         // error of the turning
    if(err > tol) {                                 // overshoot, should turn back to left
      moveLeft();
      while(true) {
        delay(1);
        testIMU();
        curryaw = ypr[0] * 180/M_PI + 180;
        err = curryaw - idlyaw;
        if(err <= tol)  break;
      }
    }else if(err < -tol) {                          // undershoot, should turn more to right
      moveRight();
      while(true) {
        delay(1);
        testIMU();
        curryaw = ypr[0] * 180/M_PI + 180;
        err = curryaw - idlyaw;
        if(err >= -tol)  break;
      }
    }else {                                         // nice turning, do nothing

    }
  }else {                                           // tDirection = 1, turned right 
    idlyaw = inityaw - angle;
    idlyaw = (idlyaw > 0)?idlyaw:(idlyaw + 360);
    err = curryaw - idlyaw;                         // error of the turning
    if(err > tol) {                                 // undershoot, should turn more to left
      moveLeft();
      while(true) {
        delay(1);
        testIMU();
        curryaw = ypr[0] * 180/M_PI + 180;
        err = curryaw - idlyaw;
        if(err <= tol)  break;
      }
    }else if(err < -tol) {                          // overshoot, should turn back to right
      moveRight();
      while(true) {
        delay(1);
        testIMU();
        curryaw = ypr[0] * 180/M_PI + 180;
        err = curryaw - idlyaw;
        if(err >= -tol)  break;
      }
    }else {                                         // nice turning, do nothing
    }
  }
}



void calMoveRightScan(float angle){
  angle = angle - 10;
  mpu.resetFIFO();
  for(int i = 0; i <175; i++) {
    testIMU();
  }
  Serial.println("Initializing IMU...");
  Serial.println("Finished initializing IMU. Entering turning...");
  testIMU();
  float inityaw = ypr[0] * 180/M_PI + 180;
  Serial.print("Initial yaw: ");
  Serial.println(inityaw);
  float calyaw;
  float temp = inityaw + angle;
  if (temp > 360)
    temp = temp - 360;
  moveRight();
  while (true) {
    testIMU();
    calyaw = ypr[0] * 180/M_PI + 180;
    if(temp < angle && calyaw > 360 - angle) {
      calyaw = calyaw - 360;
    }
    if(digitalRead(pi2teensyPin)==HIGH){
      maxLightYaw=calyaw;
    }
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw >= temp){
      break;
    }
  }
  brake();
  delay(300);
}

void return2MaxLight(float maxYaw){
  mpu.resetFIFO();
  for(int i = 0; i <175; i++) {
    testIMU();
  }
  Serial.println("Initializing IMU...");
  Serial.println("Finished initializing IMU. Entering turning...");
  testIMU();
  float inityaw = ypr[0] * 180/M_PI + 180;
  Serial.print("Initial yaw: ");
  Serial.println(inityaw);
  float calyaw;
  moveRight();
  while (true) {
    testIMU();
    calyaw = ypr[0] * 180/M_PI + 180;
    
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw >= maxYaw){
      break;
    }
  }
  brake();
  delay(300);
}


