void calMoveRight(){
  mup.resetFIFO();
  float prevyaw = 0;
  float curryaw = 0;
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
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw > temp)
      break;
  }
  brake();
  delay(3000);
}

void calMoveLeft(){
  mup.resetFIFO();
  float prevyaw = 0;
  float curryaw = 0;
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
  moveLeft(); 
  while (true) {
    testIMU();
    calyaw = ypr[0] * 180/M_PI + 180;
    Serial.print("calyaw: ");
    Serial.println(calyaw); 
    if (calyaw > temp)
      break;
  }
  brake();
  delay(3000);
}

