
//***********************************************************

void moveForward()
{   

    analogWrite(x_speed,speed);   //230 ideal 
    analogWrite(y_speed,speed);   //230 ideal 
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH);
    
    analogWrite(a_speed,speed);
    analogWrite(b_speed,speed);
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
void moveLeft()
{
    analogWrite(x_speed,150);
    analogWrite(y_speed,150);
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    analogWrite(a_speed,150);
    analogWrite(b_speed,150);
    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);

}
void moveRight()
{
    analogWrite(x_speed,250);
    analogWrite(y_speed,0);
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH); 

    analogWrite(a_speed,0); 
    analogWrite(b_speed,250);
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
  int ticks = x * 4;  //cm adjustment ratio (30*4 = 120)
  pulse_left = 0;
  pulse_right = 0;
  moveForward();
  delay(500);
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
    if (pulse_right > ticks && pulse_left > ticks){
      ticksR = pulse_right;
      ticksL = pulse_left;
      break;     
    }
  }
    brake();
    
    Serial.print("Right Ticks: ");
    Serial.println(ticksR);
    Serial.print("Left Ticks: ");
    Serial.println(ticksL);
    //Serial.print("SUM OF PULSES: ");
    //Serial.println(pulse_right+pulse_left);
    Serial.print("Variance: ");
    Serial.println(ticksR-ticksL);
    Serial.print("How far off: ");
    Serial.println(ticksR+ticksL-(ticks*2));
    Serial.println(" ");
    Serial.println(" ");
    
}


void turn(int degrees)
{
  pulse_left = 0;
  pulse_right = 0;
  
  moveRight();
  while (true)
  {
    delay(1);
    if (pulse_left > degrees*4)
      break;
  }
  brake();
}
