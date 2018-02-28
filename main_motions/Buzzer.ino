
// play tone on a piezo buzzerPin: tone shorter values produce higher frequencies
//  which is opposite beep() but avoids some math delay - similar to code by Erin Robotgrrl

void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(buzzerPin, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(buzzerPin, LOW);
     delayMicroseconds(tone1);
  }
}

// another sound producing function similar to http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
void beep (int16_t frequencyInHertz, long timeInMilliseconds) {
    long x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++) {
       digitalWrite(buzzerPin,HIGH);
       delayMicroseconds(delayAmount);
       digitalWrite(buzzerPin,LOW);
       delayMicroseconds(delayAmount);
    }
}

void chirp() {  // Bird chirp
 // for(uint16_t i=320; i>280; i--)
   //  playTone(i,9);

playTone(800, 40);
playTone(700, 30);
playTone(600, 40);
playTone(650, 50);
playTone(750, 20);
delay(100);
playTone(600, 40);
playTone(400, 20);
playTone(300, 60);
playTone(200, 80);
}

void bootTone() {
playTone(1000, 50);
playTone(2000, 40);
playTone(1000, 50);
//
////delay(100);
//
//playTone(1500, 20);
//playTone(2500, 20);
//playTone(1500, 20);
//
////delay(100);
//
//playTone(800, 20);
//playTone(900, 20);
//playTone(6000, 20);
//
////delay(100);
//
//playTone(900, 20);
//playTone(1000, 20);
//playTone(1300, 20);

}


void boopTone(){
  playTone(900, 100);
  delay(30);
  playTone(1000, 100);

}

void loseTone(){
  playTone(1000,150);
  delay(40);
  playTone(1300,200);
  playTone(1500,500);
}

void victoryTone(){
  playTone(430,150);
  delay(30);
  playTone(430,70);
  playTone(220,700);
}


void frontWallTone(){
  playTone(200, 300);
}

void dying() {  // cat meow (emphasis ow "me")
  uint16_t i;
  playTone(5100,50);        // "m" (short)
  playTone(394,180);        // "eee" (long)
  for(i=990; i<1022; i+=2)  // vary "ooo" down
     playTone(i,8);
  playTone(5100,40);        // "w" (short)
}



void meow2() {  // cat meow (emphasis on "ow")
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
     playTone(i,10);
  playTone(5100,40);       // "w" (short)
}
 
void mew() {  // cat mew
  uint16_t i;
  playTone(5100,55);       // "m"   (short)
  playTone(394,130);       // "eee" (long)
  playTone(384,35);        // "eee" (up a tiny bit on end)
  playTone(5100,40);       // "w"   (short)
}

void scale(){
  playTone(1915,950);
  delay(50);
  playTone(1700,950);
  delay(50);
  playTone(1519,950);
  delay(50);
  playTone(1432,950);
  delay(50);
  playTone(1275,950);
  delay(50);
  playTone(1136,950);
  delay(50);
  playTone(1014,950);
  delay(50);
  playTone(956,1500);
 }
void ruff() {   // dog ruff
  uint16_t i;
  for(i=890; i<910; i+=2)     // "rrr"  (vary down)
     playTone(i,3);
  playTone(1664,150);         // "uuu" (hard to do)
  playTone(12200,70);         // "ff"  (long, hard to do)
}
 
void arf() {    // dog arf
  uint16_t i;
  playTone(890,25);          // "a"    (short)
  for(i=890; i<910; i+=2)    // "rrr"  (vary down)
     playTone(i,5);
  playTone(4545,80);         // intermediate
  playTone(12200,70);        // "ff"   (shorter, hard to do)
}
 

void laserTone() {
  for(uint16_t i=50; i<900; i++)  {
     playTone(i,1);
  }
}
