
//***********************************************************

void moveForward()
{   
    analogWrite(x_speed,150);
    analogWrite(y_speed,150);
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH);
    
    analogWrite(a_speed,150);
    analogWrite(b_speed,150);
    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);
}

void moveForwardTen(){

  pulse_left = 0;
  pulse_right=0;
  moveForward();
  while(true){
  delay(1);
  if (pulse_right + pulse_left > 1100 ){
    countMoves = countMoves+1;
    /*
    Serial.println("SUM OF PULSES: ");
    Serial.print(pulse_right+pulse_left);
    Serial.println("count: ");
    Serial.print(countMoves);
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
    analogWrite(x_speed,150);
    analogWrite(y_speed,150);
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH); 

    analogWrite(a_speed,150);
    analogWrite(b_speed,150);
    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_a2,HIGH);
    digitalWrite(motor_a1,LOW);
}
void brake()
{
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,LOW);
}
