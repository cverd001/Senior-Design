
int optTicks = 0; // number of ticks for desired location
int optCid = 0; // column number for desired location

//int ticksL; // current tick count Left
//int ticksR; // current tick count Right

/* flag to check if robot was moving up/down or left/right
   when max sunlight was acquired. If this flag is not 0 or
   1 when checked results in error.
   directionFlag = 1: was moving vertically
   directionFlag = 0: was moving horizontally
   directionFlag = anything else: ERROR */
int directionFlag;

int maxPhotoV = 0;
int light = 0;      // adc reading ...of solar panel?
int avg_ldr = 0;    // photoresistors average reading
const int photoThresh = 5000;//390  // adc reading threshold of photoresistors!! WAS 14*** 900
const int solarThresh = 150;  //!! REDO THIS AFTER CONNECTING BATTERY TO CHARGE CIRCUIT !!!!
const int ldr_threshold = 0;    // average photoresistors threshold
int spotsMax = 0;     //max Solar voltage readings

int current_state = 0, previous_state = 0;
int dtime = 100;          // delay time for each tracking movement


void PerformTraverseAlg()
{

  delay(1000);
  Serial.println("Starting Traverse Alg");
//  rows = 3; // test
//  columns = 5; // test
  directionFlag = -1; // -1 is used as debugging check
  int stopFlag = 0; //Flag to indicate if threshold sunlight voltage has been found
  maxPhotoV = 0;

  for (int Cid = 0; Cid < rows; Cid++)
  {
    int maxTicks = (columns - 1) * 30 * 1.6;  // 1.6 ticks per cm
    Serial.println("Moving Forward");
    moveForward();
    delay(200);//20
    ticksL = 0;
    ticksR = 0;
    while (true)
    {
      delay(1);
      if (ticksR % 8 == 0) // take reading every 5cm
      {
        //Serial.println("8 Ticks Reading");
        int light = readPhotoresistors();
        Serial.println(light);
        //int light = 0; // test
        if (light > maxPhotoV)
        {
          maxPhotoV = light;
          optTicks = (ticksL + ticksR) / 2;
          optCid = Cid;
          if (Cid % 2 == 1)
            optTicks = maxTicks - optTicks; // maxTicks - tick number when bot is going down instead of up
          directionFlag = 1; // flag, bot was moving up/down
          Serial.println("Flag 1");
        }
        if (maxPhotoV >= photoThresh)
        {
          stopFlag = 1; // signals that max threshold has been reached
          break;
        }
      }
      if (ticksR >= maxTicks && ticksL >= maxTicks)
      {
        //Serial.println("break");
        break;
      }
    }
    //Serial.println("break brake");
    brake();
    
    if (stopFlag)
    {
      victoryTone();
      Serial.println("Stop Flag");
      break;
    }
    
    delay(500);
    if (Cid != (rows - 1))
    {
      if (Cid % 2 == 0) // if even, turn right
        //turnRightBurst(27);
        calMoveRight(90);
      else
        calMoveLeft(90);
       //turnLeftBurst(27);
      delay(500);

      // Move forward 1 grid space
      Serial.println("Move forward1 grid");
      moveForward();
      delay(20);
      ticksL = 0;
      ticksR = 0;
      while (true) // check while moving 1 grid space right
      {
        delay(1);
        if (ticksR % 8 == 0) // take reading every 5cm
        {
          int light = readPhotoresistors();
          Serial.println(light);
          //int light = 0; // test
          if (light > maxPhotoV)
          {
            maxPhotoV = light;
            optTicks = (ticksL + ticksR) / 2; // how many ticks to the right of Cid
            optCid = Cid;
            directionFlag = 0; // flag, bot was moving right
          }
          if (maxPhotoV >= photoThresh)
          {
            stopFlag = 1; // signals that max threshold has been reached
            break;
          }
        }
        if (ticksR >= 48 && ticksL >= 48) // 1 grid space
          break;
      }
      brake();
      if (stopFlag)
      {
        victoryTone();
        Serial.println("Stop Flag"); 
        break;
      }
        

      delay(500);
      if (Cid % 2 == 0) // if even, turn right
        calMoveRight(90);
        //turnRightBurst(27);
      else
        calMoveLeft(90);
        //turnLeftBurst(27);
      delay(500);

    }

  }
  delay(1000);
  if (directionFlag)
    Serial.println("Was moving up/down");
  else
    Serial.println("Was moving right");
  Serial.println("maxPhotoV:");
  Serial.println(maxPhotoV);
  Serial.println("OPTTICKS:");
  Serial.println(optTicks);
  Serial.println("OPTCID:");
  Serial.println(optCid);
  


  if (!stopFlag){
    ReturnToMax();
    victoryTone();
  }
  Spin();
  chirp();
  delay(5000);
  chirp();
  Tracking();
  bootTone();
  bootTone();
  //Monitor();
}

void ReturnToMax()
{
  boopTone();
  //using optTicks, optCid, directionFlag parameters
  int xTicks = 0; // number of ticks bot must move along x-axis
  int yTicks = 0; // number of ticks bot must move along y-axis
  int zTicks = 0; // pythagorean theorem
  int zDegrees = 0; // degrees of triangle

  if (directionFlag == 0) // was moving right when max sunlight detected
  {
    xTicks = (rows - optCid - 1) * 48 - optTicks;
    if ((rows - 1 + optCid) % 2 == 0)
    {
      Serial.println("Same edge of grid");
      yTicks = 0; // same edge of grid as max sunlight location
    }
    else
    {
      Serial.println("Opposite edge of grid");
      yTicks = 48 * (columns - 1); // opposite edge of grid      
    }
  }
  else if (directionFlag == 1) // was moving up/down when max sunlight detected
  {
    xTicks = (rows - optCid - 1) * 48;
    if (rows % 2 == 0) // same x-edge of origin
    {
      Serial.println("Same edge of grid as origin");
      yTicks = optTicks;
    }
    else
    {
      Serial.println("Opposite edge of grid as origin");
      yTicks = 48 * (columns - 1) - optTicks;
    }

  }
  else
    Serial.println("ERROR: directionFlag != 0,1");

  zTicks = sqrt(sq(xTicks) + sq(yTicks));

  if (yTicks == 0)
    zDegrees = 90;
  else
    zDegrees =  round( atan2 (xTicks, yTicks) * 180 / 3.14159265 ); // radians to degrees and rounding

  zDegrees = 180 - zDegrees;

  Serial.println("Degrees:");
  Serial.println(zDegrees);
  Serial.println("Ticks:");
  Serial.println(zTicks);

  if (rows % 2 == 0)
    calMoveRight(zDegrees); // same x-edge of origin (on the bottom)
  else
    calMoveLeft(zDegrees); // (on the top)


  
  moveForwardAdj(zTicks); // FIX

  delay(1000);
}

void Spin() // RESOLUTION = 12; 132 ticks for turnRight spinning 360; 11 ticks each
{
  int spots[22] = {0};
  int i = 0;
  int deg_id = 0;

  ticksR = 0;
  for (i = 0; i < 22; i++) {
    ticksR = 0;
    spots[i] = analogRead(solarPin);
    Serial.print("Solar Panel Voltage reading of current spot: ");
    Serial.println(spots[i]);
    if (spots[i] > spotsMax) {
      spotsMax = spots[i];
      deg_id = i;
      Serial.print("Setting max spot to: ");
      Serial.println(deg_id);
    }
    moveRight();
    while (true) {
      delay(1);
      if (ticksR > 6) {
        break;
      }
    }
    //Serial.println("11 ticks! braking!");
    Serial.print("i: ");
    Serial.println(i);
    brake();
    delay(200);
  }

  chirp();
  Serial.print("Spinning back to: ");
  Serial.println(deg_id); 
  ticksR = 0;
  moveRight();
  while (true)  // spin back
  {
    if (ticksR > 6 * deg_id)
    {
      Serial.println("move Right (spinback)");
      Serial.print("deg_d = ");
      Serial.println(deg_id);
      Serial.print("TicksR = ");
      Serial.println(ticksR);
      break;
    }
  }
  brake();
  delay(7000);
  Serial.println("Done (final brake)");
}

void Monitor() //check every 20 seconds if light conditions change
{
    chirp();
    chirp();
  while (true)
  {
    delay(20000);     // delay 20 sec for demo
    light = readSolarVoltage();
    if (light >= spotsMax-25){
      chirp();
      continue;       // continue enjoy ample sunlights here!
    }
    else{
      bootTone();
      bootTone();
      bootTone();
      break;
    }

  }
}

void Tracking()
{
  int ldrR, ldrL;
  int diffRL = 0;
  int tol = 70;  // FIX
  int deg_id = 0;

  while (true)
  {      
    ldrR = analogRead(photoR2Pin);  // FIX
    ldrL = analogRead(photoR1Pin);   // FIX
    Serial.print("Right Value: ");
    Serial.print(ldrR);
    Serial.print("    Left Value: ");
    Serial.println(ldrL);
    diffRL = ldrL - ldrR;
    diffRL = abs(diffRL);
    if (readSolarVoltage()<=spotsMax-15) // already checked 360 degrees, should continue searching the area
    {
      bootTone();
      delay(3000);
      if(readSolarVoltage()<=spotsMax-15){
        loseTone();
        break;
      }
    }
    else if ( tol < diffRL ) // check if the difference is in the tolerance else change horizontal angle
    {
      ticksR = 0; ticksL = 0;
      if (ldrL > ldrR)  // left R bigger, left sunlight weaker, slightly spin right
      {
        deg_id ++;
        moveLeft();
        while (true)    // RESOLUTION = 22; 132 ticks for turnRight spinning 360; 6 ticks each
        {
          if (ticksR > 3)
            break;
        }
        brake();
        delay(100);
      }
      else if (ldrL < ldrR) // right R bigger, right sunlight weaker, slightly spin left
      {
        deg_id ++;
        moveRight();
        while (true)
        {
          if (ticksR > 3)
            break;
        }
        brake();
        delay(100);
      }
      else if (ldrL == ldrR)
      {
        chirp();
        Serial.println("right and left are same");
      }
    }
    delay(dtime);
  }
}

