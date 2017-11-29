
//***********************************************************
void moveForward()
{   
    analogWrite(x_speed,255);
    analogWrite(y_speed,255);
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH);
}
void moveBack()
{
    analogWrite(x_speed,100);
    analogWrite(y_speed,100);
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 
}
void moveLeft()
{
    analogWrite(x_speed,100);
    analogWrite(y_speed,100);
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,HIGH);
    digitalWrite(motor_x2,HIGH);
    digitalWrite(motor_x1,LOW); 
}
void moveRight()
{
    analogWrite(x_speed,100);
    analogWrite(y_speed,100);
    digitalWrite(motor_y2,HIGH);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,HIGH); 
}
void brake()
{
    digitalWrite(motor_y2,LOW);
    digitalWrite(motor_y1,LOW);
    digitalWrite(motor_x2,LOW);
    digitalWrite(motor_x1,LOW); 
}
