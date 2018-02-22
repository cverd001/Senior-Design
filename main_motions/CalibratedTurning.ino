void calMoveRight(){
  mpu.resetFIFO();
  Serial.println("mpu Reset");
  float prevyaw = 0;
  float curryaw = 1;
  while(prevyaw < curryaw) {  // to wait until stable reading 
    testIMU();
    prevyaw = curryaw;
    curryaw = ypr[0] * 180/M_PI;
  }
  float inityaw = ypr[0] * 180/M_PI + 180;
  Serial.print("Initial yaw: ");
  Serial.println(inityaw);
  float calyaw = inityaw;
  float temp = inityaw + 90;
  if (temp > 360)
    temp = temp - 360;
  moveRight();
  while (true) {
    testIMU();
    calyaw = ypr[0] * 180/M_PI + 180;
    if(temp <= 90 && calyaw >= 270) {
      calyaw = calyaw -360;
    }
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw > temp){
      Serial.println("Cal > Yaw");
      break;
    }
  }
  brake();
  Serial.println("Braking");
  delay(300);
}

void calMoveLeft(){
  mpu.resetFIFO();
  float prevyaw = 0;
  float curryaw = 1;
  while(prevyaw < curryaw) {  // to wait until stable reading 
    testIMU();
    prevyaw = curryaw;
    curryaw = ypr[0] * 180/M_PI;
  }
  float inityaw = ypr[0] * 180/M_PI + 180;
  Serial.print("Initial yaw: ");
  Serial.println(inityaw);
  float calyaw = inityaw;
  float temp = inityaw - 90;
  if (temp < 0)
    temp = temp + 360;
  moveLeft(); 
  while (true) {
    testIMU();
    calyaw = ypr[0] * 180/M_PI + 180;
    if(temp >= 270 && calyaw <= 90) {
      calyaw = calyaw + 360;
    }
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw < temp)
      break;
  }
  brake();
  delay(300);
}

