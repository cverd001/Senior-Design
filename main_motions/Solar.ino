
float readSolarVoltage()
{
  int R1 = 0;
  int R2 = 0;
  int value = adc->analogRead(adc_read); // read a new value, will return ADC_ERROR_VALUE if the comparison is false.
  return (1+R1/R2)*value*3.3/adc->getMaxValue(ADC_0);
  
}


float readPhotoresistors()
{
  float x = 0;
 return x;
 
}




