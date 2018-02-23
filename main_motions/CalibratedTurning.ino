float calMoveRight(float angle){
  //angle = angle - 10;
  mpu.resetFIFO();
  //Serial.println("mpu FIFO Reset");
  float prevyaw = 0;
  float curryaw = 1;
  //Serial.println("Initializing IMU...");
  while(prevyaw < curryaw) {  // to wait until stable reading 
    testIMU();
    prevyaw = curryaw;
    curryaw = ypr[0] * 180/M_PI;
  }
  //Serial.println("Finished initializing IMU. Entering turning...");
  testIMU();
  float inityaw = ypr[0] * 180/M_PI + 180;
  //Serial.print("Initial yaw: ");
  //Serial.println(inityaw);
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
    //Serial.print("calyaw: ");
    //Serial.println(calyaw); 
    if (calyaw >= temp){
      break;
    }
  }
  brake();
  delay(300);
  return inityaw;
}

float calMoveLeft(float angle) {
  mpu.resetFIFO();
  Serial.println("mpu FIFO Reset");
  float prevyaw = 0;
  float curryaw = 1;
  Serial.println("Initializing IMU...");
  while(prevyaw < curryaw) {  // to wait until stable reading 
    testIMU();
    prevyaw = curryaw;
    curryaw = ypr[0] * 180/M_PI;
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
  return inityaw;
}

void calMoving(float inityaw, float angle, bool tDirection) {
  mpu.resetFIFO();
  testIMU();
  float curryaw = ypr[0] * 180/M_PI + 180;
  float idlyaw;                                     // ideal yaw after turning
  float err; 
  float tol = 5;
  if(tDircection == 0) {                            // turned right 
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
      break;
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
      break;
    }
  }
}

