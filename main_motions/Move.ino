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

void turnRightBurst(int count){
  //delay(1000);
  //chirp();
    int counterI=0;
    while(counterI<=count){ // 27
      counterI++;
      //Serial.println("turn right");
      moveRightPower();
      delay(50);
      //Serial.println("brake");
      brake();
      delay(250);
      //Serial.println(counterI);
    }
}

void turnLeftBurst(int count){
  //delay(1000);
  //chirp();
    int counterI=0;
    while(counterI<=count){ // 27
      counterI++;
      //Serial.println("turn right");
      moveLeftPower();
      delay(50);
      //Serial.println("brake");
      brake();
      delay(250);
      //Serial.println(counterI);
    }
}


void turnRightBurst2(){
  delay(1000);
  chirp();
    int counterI=0;
    while(counterI<=27){
      counterI=counterI+1;
      //Serial.println("turn right");
      moveRightPower();
      delay(50);
      //Serial.println("brake");
      brake();
      delay(250);
      //Serial.println(counterI);
    }
}
