
int readSolarVoltage()
{
  int solarReading = analogRead(solarPin);
  Serial.print("Solar panel raw reading: ");
  Serial.println(solarReading);
  return solarReading;
}


int readPhotoresistors()
{
  int a = analogRead(photoR1Pin);
  int b = analogRead(photoR2Pin);
  int x = (a + b) /2;
  return x;
}

int readPhotoRight(){
  int r = analogRead(photoR2Pin);
  return r;
}

int readPhotoLeft(){
  int l = analogRead(photoR1Pin);
  return l;
}

void printPhotoReadings(){
 Serial.println(readPhotoresistors());
 Serial.print("left:");
 Serial.println(readPhotoLeft());
 Serial.print("right:");
 Serial.println(readPhotoRight());
  delay(100);
}
