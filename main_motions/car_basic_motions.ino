
//***********************************************************

/*
Motor a = Front Left 
Motor b = Front Right

Motor x = Back Right
Motor y = Back Left

a---b
|   |
|   |
y---x


B is too strong!!!
*/



void moveForward()
{   

    analogWrite(x_speed,250); //180
    analogWrite(y_speed,250); //250
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH);
    
    analogWrite(a_speed,250); //250
    analogWrite(b_speed,165);//180
    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);
  

/*   
    analogWrite(a_speed,0);
    analogWrite(b_speed,0);
    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);
  */ 
}

void moveForwardTen(){

  pulse_left = 0;
  pulse_right=0;
  moveForward();
  while(true){
  delay(1);
  //if (pulse_right + pulse_left > 400 ){
  if (pulse_right > 200 && pulse_left > 200 ){
   /*
    Serial.println("SUM OF PULSES: ");
    Serial.print(pulse_right+pulse_left);
    Serial.println("Variance: ");
    Serial.print(pulse_right-pulse_left);
   
    */
    break;
    }
  }
  brake();
}

void moveBack()
{
    analogWrite(x_speed,100);
    analogWrite(y_speed,100);
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    analogWrite(a_speed,100);
    analogWrite(b_speed,100);
    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,HIGH);
    digitalWrite(motor_a1,LOW);
}
void moveRight()
{
    analogWrite(x_speed,255);
    analogWrite(y_speed,255);
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    analogWrite(a_speed,255);
    analogWrite(b_speed,190);
    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);

}
void moveLeft()
{
    analogWrite(x_speed,255);
    analogWrite(y_speed,190);
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH); 

    analogWrite(a_speed,255); 
    analogWrite(b_speed,255);
    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_a2,HIGH);
    digitalWrite(motor_a1,LOW);
}
void brake()
{
    analogWrite(x_speed,0);
    analogWrite(y_speed,0);
    analogWrite(a_speed,0);
    analogWrite(b_speed,0);
  

    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,LOW);

}

void brakeRight()
{
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,LOW);
}

void brakeLeft()
{
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,LOW);

    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,LOW);
}

// 50cm = 200ticks
// 200 ticks=52 cm
void moveForwardAdj (int x)
{
  int ticks = x * 4;  //cm adjustment ratio (30*4 = 120)
  pulse_left = 0;
  pulse_right = 0;
  moveForward();
  while (true)
  {
    delay(1);
    if (pulse_right > ticks && pulse_left > ticks)     
     break;
  }
  brake();
    Serial.print("Right Ticks: ");
    Serial.println(pulse_right);
    Serial.print("Left Ticks: ");
    Serial.println(pulse_left);
    //Serial.print("SUM OF PULSES: ");
    //Serial.println(pulse_right+pulse_left);
    Serial.print("Variance: ");
    Serial.println(pulse_right-pulse_left);
    Serial.print("How far off: ");
    Serial.println(pulse_right+pulse_left-(ticks*2));
    Serial.println(" ");
    Serial.println(" ");
}


void moveForwardAdj2 (int x)
{
  int ticks = x ;  //cm adjustment ratio (30*4 = 120)
  pulse_left = 0;
  pulse_right = 0;
  moveForward();
  delay(20);
  pulse_left = 0;
  pulse_right = 0;
  while (true)
  {
    delay(1);
/*    if(pulse_right > ticks){
      playTone(700,200);
    }
    if(pulse_left>ticks){
      playTone(300,200);
    }
    */
    if (pulse_right >= ticks && pulse_left >= ticks){
      break;     
    }
  }
      brake();
    
    Serial.print("Right Ticks: ");
    Serial.println(pulse_right);
    Serial.print("Left Ticks: ");
    Serial.println(pulse_left);
    //Serial.print("SUM OF PULSES: ");
    //Serial.println(pulse_right+pulse_left);
    Serial.print("Variance: ");
    Serial.println(ticksR-ticksL);
    Serial.print("How far off: ");
    Serial.println(ticksR+ticksL-(ticks*2));
    Serial.println(" ");
    Serial.println(" ");
    
}


void turnLeft(int degrees)
{
  pulse_left = 0;
  pulse_right = 0;
  
  moveLeft();
  delay(15);
  pulse_left = 0;
  pulse_right = 0;  
  while (true)
  {
    delay(1);
    if (pulse_left > degrees && pulse_right > degrees)
      break;
  }
  brake(); 
}

void turnRight(int degrees)
{
  pulse_left = 0;
  pulse_right = 0;
  
  moveRight();
  delay(15);
  pulse_left = 0;
  pulse_right = 0;  
  while (true)
  {
    delay(1);
    if (pulse_left > degrees && pulse_right > degrees)
      break;
  }
  brake();
}
