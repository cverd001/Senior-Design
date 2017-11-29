// accuracy control of car 
void camera_rotation()
{
  angle = 10;
  while(bluetooth_command != 'y' && angle <= 170)
  {
    myservo.write(angle);
    delay(1000);
    angle += 10;
  }
  
  if(bluetooth_command == 'y') flag = 1;
  else flag = 0;
  myservo.write(90); 
  delay(2000);
    
}

// encoder calculation
void encoder_calculation()
{
  if(angle > 90 && angle <= 170)  // turn left
  {
    while(pulse_left <= angle || pulse_right <= angle)
    {
      moveLeft();
      Serial.print("pulse left:"); //
      Serial.println(pulse_left); //
    }
  }
  if(angle < 90 && angle >= 10)  // turn left
  {
    while(pulse_left <= angle || pulse_right <= angle)
    {
      moveLeft();
      Serial.print("pulse right:"); //
      Serial.println(pulse_right); // 
    }
  }
  else
  {
    brake();
    delay(1000);
    moveForward();
  }
  detachInterrupt(encoder_pinLeft);
  detachInterrupt(encoder_pinRight);
  //pulse_left = 0;
  //pulse_right = 0;
  attachInterrupt(0, encoder_counterLeft, FALLING);
  attachInterrupt(1, encoder_counterRight, FALLING);
} 
void encoder_counterLeft()
{
  pulse_left ++;
  Serial.println(pulse_left);
}

void encoder_counterRight()
{
  pulse_right ++;
  Serial.println(pulse_right);
}

