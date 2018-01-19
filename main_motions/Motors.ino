/*-----------------------------------------------
Motor a = Front Left 
Motor b = Front Right *this motor is stronger
Motor x = Back Right
Motor y = Back Left

a---b
|   |
|   |
y---x

-b is too strong!!!
--------------------------------------------------
Movement Tick Settings
MoveforwardAdj2: 48 = 1 block (30cm) 48 too high??
turnLeft: 27 = 90 degrees
turnRight: 33 = 90 degrees
--------------------------------------------------
*/

void moveForward()
{   
    analogWrite(x_speed,250); //250
    analogWrite(y_speed,250); //250
    analogWrite(a_speed,250); //250
    analogWrite(b_speed,200); //165 Motor_b stronger causes veer
        
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH);
   
    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);
}

void moveRight()
{
    analogWrite(x_speed,255); //255
    analogWrite(y_speed,255); //255
    analogWrite(a_speed,255); //255
    analogWrite(b_speed,210); //was 190
    
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);
}

void moveLeft()
{
    analogWrite(x_speed,255); //255
      analogWrite(y_speed,210); //was 190
    analogWrite(a_speed,255); //255
    analogWrite(b_speed,255); //255
    
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH); 

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

void moveBack()   //remove?
{
    analogWrite(x_speed,100);   //PWM values need adjust
    analogWrite(y_speed,100);
    analogWrite(a_speed,100);
    analogWrite(b_speed,100);
    
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 
    
    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,HIGH);
    digitalWrite(motor_a1,LOW);
}
