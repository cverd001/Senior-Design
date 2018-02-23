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
    analogWrite(b_speed,155); //165 Motor_b stronger causes veer 
        
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
    analogWrite(b_speed,190); //was 190
    
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
      analogWrite(y_speed,190); //was 190
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


void moveRightSlow()
{
    analogWrite(x_speed,180); //255
    analogWrite(y_speed,180); //255
    analogWrite(a_speed,180); //255
    analogWrite(b_speed,170); //was 190
    
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);
}


void moveRightPower()
{   
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);

    analogWrite(x_speed,255); //255
    analogWrite(y_speed,255); //255
    analogWrite(a_speed,255); //255
    analogWrite(b_speed,240); //was 190
}

void moveLeftPower()
{
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH); 

    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,HIGH);
    digitalWrite(motor_a2,HIGH);
    digitalWrite(motor_a1,LOW);

    analogWrite(x_speed,255); //255
    analogWrite(y_speed,255); //was 190
    analogWrite(a_speed,255); //255
    analogWrite(b_speed,240); //255
}

void Yonly()
{
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,LOW);  

    analogWrite(x_speed,0); //255
    analogWrite(y_speed,230); //was 190
    analogWrite(a_speed,0); //255
    analogWrite(b_speed,0); //255    
}

void Xonly()
{
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH); 

    digitalWrite(motor_b2,LOW);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,LOW);  

    analogWrite(x_speed,230); //255
    analogWrite(y_speed,0); //was 190
    analogWrite(a_speed,0); //255
    analogWrite(b_speed,0); //255    
}

void moveRightPower3()
{   
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);

    analogWrite(x_speed,0); //255
    analogWrite(y_speed,255); //255
    analogWrite(a_speed,0); //255
    analogWrite(b_speed,240); //was 190
}



void moveRightPowerGradual()
{

    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 

    digitalWrite(motor_b2,HIGH);
    digitalWrite(motor_b1,LOW);
    digitalWrite(motor_a2,LOW);
    digitalWrite(motor_a1,HIGH);
      
    analogWrite(x_speed,4); //255
    analogWrite(y_speed,4); //255
    analogWrite(a_speed,4); //255
    analogWrite(b_speed,3); //was 190
    delay(3);

    analogWrite(x_speed,8); //255
    analogWrite(y_speed,8); //255
    analogWrite(a_speed,8); //255
    analogWrite(b_speed,5); //was 190
    delay(3);

    analogWrite(x_speed,15); //255
    analogWrite(y_speed,15); //255
    analogWrite(a_speed,15); //255
    analogWrite(b_speed,10); //was 190
    delay(3);

    analogWrite(x_speed,35); //255
    analogWrite(y_speed,35); //255
    analogWrite(a_speed,35); //255
    analogWrite(b_speed,20); //was 190
    delay(3);
    
    analogWrite(x_speed,45); //255
    analogWrite(y_speed,45); //255
    analogWrite(a_speed,45); //255
    analogWrite(b_speed,30); //was 190
    delay(3);

    analogWrite(x_speed,55); //255
    analogWrite(y_speed,55); //255
    analogWrite(a_speed,55); //255
    analogWrite(b_speed,40); //was 190
    delay(3);

    analogWrite(x_speed,65); //255
    analogWrite(y_speed,65); //255
    analogWrite(a_speed,65); //255
    analogWrite(b_speed,50); //was 190
    delay(3);

    analogWrite(x_speed,75); //255
    analogWrite(y_speed,75); //255
    analogWrite(a_speed,75); //255
    analogWrite(b_speed,60); //was 190
    delay(3);

    analogWrite(x_speed,85); //255
    analogWrite(y_speed,85); //255
    analogWrite(a_speed,85); //255
    analogWrite(b_speed,70); //was 190
    delay(3);

    analogWrite(x_speed,95); //255
    analogWrite(y_speed,95); //255
    analogWrite(a_speed,95); //255
    analogWrite(b_speed,80); //was 190
    delay(3);

    analogWrite(x_speed,105); //255
    analogWrite(y_speed,105); //255
    analogWrite(a_speed,105); //255
    analogWrite(b_speed,90); //was 190
    delay(3);

    analogWrite(x_speed,115); //255
    analogWrite(y_speed,115); //255
    analogWrite(a_speed,115); //255
    analogWrite(b_speed,100); //was 190
    delay(3);

    analogWrite(x_speed,125); //255
    analogWrite(y_speed,125); //255
    analogWrite(a_speed,125); //255
    analogWrite(b_speed,110); //was 190
    delay(3);

    analogWrite(x_speed,135); //255
    analogWrite(y_speed,135); //255
    analogWrite(a_speed,135); //255
    analogWrite(b_speed,120); //was 190
    delay(3);

    analogWrite(x_speed,145); //255
    analogWrite(y_speed,145); //255
    analogWrite(a_speed,145); //255
    analogWrite(b_speed,130); //was 190
    delay(4);

    analogWrite(x_speed,155); //255
    analogWrite(y_speed,155); //255
    analogWrite(a_speed,155); //255
    analogWrite(b_speed,140); //was 190
    delay(4);


    analogWrite(x_speed,165); //255
    analogWrite(y_speed,165); //255
    analogWrite(a_speed,165); //255
    analogWrite(b_speed,150); //was 190
    delay(4);

    analogWrite(x_speed,175); //255
    analogWrite(y_speed,175); //255
    analogWrite(a_speed,175); //255
    analogWrite(b_speed,160); //was 190
    delay(4);

    analogWrite(x_speed,285); //255
    analogWrite(y_speed,285); //255
    analogWrite(a_speed,285); //255
    analogWrite(b_speed,170); //was 190
    delay(4);

    analogWrite(x_speed,295); //255
    analogWrite(y_speed,295); //255
    analogWrite(a_speed,295); //255
    analogWrite(b_speed,180); //was 190
    delay(4);

    analogWrite(x_speed,205); //255
    analogWrite(y_speed,205); //255
    analogWrite(a_speed,205); //255
    analogWrite(b_speed,190); //was 190
    delay(4);

    analogWrite(x_speed,215); //255
    analogWrite(y_speed,215); //255
    analogWrite(a_speed,215); //255
    analogWrite(b_speed,200); //was 190
    delay(4);

    analogWrite(x_speed, 235); //255
    analogWrite(y_speed,235); //255
    analogWrite(a_speed, 235); //255
    analogWrite(b_speed, 220); //was 190
    delay(4);

    analogWrite(x_speed,245); //255
    analogWrite(y_speed,245); //255
    analogWrite(a_speed,245); //255
    analogWrite(b_speed,230); //was 190
    delay(4);
   

    analogWrite(x_speed,255); //255
    analogWrite(y_speed,255); //255
    analogWrite(a_speed,255); //255
    analogWrite(b_speed,240); //was 190

}
