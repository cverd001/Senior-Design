
float readSolarVoltage()
{
  int R1 = 0;
  int R2 = 0;
  int value = adc->analogRead(adc_read); // read a new value, will return ADC_ERROR_VALUE if the comparison is false.
  return (1+R1/R2)*value*3.3/adc->getMaxValue(ADC_0);
  
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


