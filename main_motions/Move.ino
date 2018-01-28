void moveForwardAdj (int x)
{
  int ticks = x ;  //cm adjustment ratio (30*4 = 120)
  ticksL = 0;
  ticksR = 0;
  moveForward();
  delay(20);
  ticksL = 0;
  ticksR = 0;
  while (true)
  {
    delay(1);
    if (ticksR >= ticks && ticksL >= ticks){
      break;     
    }
  }
      brake();
    
    Serial.print("Right Ticks: ");
    Serial.println(ticksR);
    Serial.print("Left Ticks: ");
    Serial.println(ticksL);
    //Serial.print("SUM OF PULSES: ");
    //Serial.println(ticksR+ticksL);
    Serial.print("Variance: ");
    Serial.println(ticksR-ticksL);
    Serial.print("How far off: ");
    Serial.println(ticksR+ticksL-(ticks*2));
    Serial.println(" ");
    Serial.println(" ");
    
}

void MoveForwardTicks( int ticks)
{

  
}

void turnLeft(int degrees)
{
  ticksL = 0;
  ticksR = 0;
  
  moveLeft();
  delay(15);
  ticksL = 0;
  ticksR = 0;  
  while (true)
  {
    delay(1);
    if (ticksL > degrees && ticksR > degrees)
      break;
  }
  brake(); 
}

void turnRight(int degrees)
{
  ticksL = 0;
  ticksR = 0;
  
  moveRight();
  delay(15);
  ticksL = 0;
  ticksR = 0;  
  while (true)
  {
    delay(1);
    if (ticksL > degrees && ticksR > degrees)
      break;
  }
  brake();
}

void moveRightComp(int degrees)
{
 
  ticksL = 0;
  ticksR = 0;
  
  moveRight();
  delay(15);
  ticksL = 0;
  ticksR = 0;  
  while (true)
  {
    delay(1);
    if (ticksL > degrees && ticksR > degrees)
      break;
  }
  brake();
}
