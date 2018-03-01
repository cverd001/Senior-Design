void loadMenu(){
  delay(200);
  ticksL = 0;
  ticksR = 0;
  while(true){
    if(readPhotoresistors()<100){
      Serial.print("Chosen Size is: ");
      Serial.println(rows);
      break;
    }
    
    else if(ticksR>100){
      ticksR=0;
    }
    
    else if(ticksR>75){
      fiveTone();
      rows=5;
      columns=5;
      Serial.print("Current Size is: ");
      Serial.println(rows);
    }
    
    else if(ticksR>50){
      fourTone();
      rows=4;
      columns=4;
      Serial.print("Current Size is: ");
      Serial.println(rows);
    }
    
    else if(ticksR>25){
      threeTone();
      rows=3;
      columns=3;
      Serial.print("Current Size is: ");
      Serial.println(rows);
    }
   else if(ticksR<=25){
      twoTone();
      rows =2;
      columns=2;
      Serial.print("Current Size is: ");
      Serial.println(rows);      
    }
  }

  laserTone();
  delay(5000);
  chirp();
  
}
