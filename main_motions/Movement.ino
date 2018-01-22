


#define START 0
#define STOP 1
#define SPIN 2
#define SEARCH 3
#define MONITOR 4
#define RETURN_TO_MAX 5
#define TRACKING 6

int xmax, ymax; // grid dimensions
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

int maxSolarV = 0;
int adc_vol = 0;      // adc reading
int avg_ldr = 0;    // photoresistors average reading
const int thresholdV = 14;  // adc reading threshold
const int ldr_threshold = 0;    // average photoresistors threshold 

int current_state = 0, previous_state = 0;
int dtime = 5000;          // delay time for each tracking movement

void searching()
{
  //initialize
  current_state = SEARCH; // test

  switch(current_state)
  {
    case START: 
    {
      delay(500);
      previous_state = current_state;
      current_state = SEARCH;
    }
    case SEARCH:
    {
      xmax = 5; // test
      ymax = 5; // test
    directionFlag = -1; // -1 is used as debugging check
    int stopFlag = 0; //Flag to indicate if threshold sunlight voltage has been found
    
    for (int Cid = 0; Cid < xmax; Cid++)
    {
        int maxTicks = (ymax - 1) * 30 * 1.6;  // 1.6 ticks per cm
        moveForward();
        delay(20);
        ticksL = 0;
        ticksR = 0;
        while (true)
        {
          delay(1);
          if (ticksR % 8 == 0) // take reading every 5cm
          {
            //float adc_vol = readPhotoresistors(); // change to double/float?
            float adc_vol = 0; // test
            if (adc_vol > maxSolarV)
            {
              maxSolarV = adc_vol;
              optTicks = (ticksL + ticksR) / 2;
              optCid = Cid;
              if (Cid % 2 == 1)
                optTicks = maxTicks - optTicks; // maxTicks - tick number when bot is going down instead of up
              directionFlag = 1; // flag, bot was moving up/down
            }
            if (maxSolarV >= thresholdV)
            {
              stopFlag = 1; // signals that max threshold has been reached
              break;
            }
          }
          if (ticksR >= maxTicks && ticksL >= maxTicks)
            break;    
           
        }
        brake();
        if (stopFlag)
          break;
        if (Cid % 2 == 0) // if even, turn right
          turnRight(46);
        else
          turnLeft(30);
          
        // Move forward 1 grid space
        moveForward();
        delay(20);
        ticksL = 0;
        ticksR = 0;
        while (true) // check while moving 1 grid space right
        {
          delay(1);
          if (ticksR % 8 == 0) // take reading every 5cm
          {
            //float adc_vol = readSolarVoltage(); // FIX
            float adc_vol = 0; // test
            if (adc_vol > maxSolarV)
            {
              maxSolarV = adc_vol;
              optTicks = (ticksL + ticksR) / 2; // how many ticks to the right of Cid
              optCid = Cid;
              directionFlag = 0; // flag, bot was moving right
            }
            if (maxSolarV >= thresholdV)
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
          break;
          
        if (Cid % 2 == 0) // if even, turn right
          turnRight(46);
        else
          turnLeft(30);
        
    }

    if (stopFlag)
    {
      previous_state = current_state;
      current_state = STOP;
    }
    else
    {
      previous_state = current_state;
      current_state = RETURN_TO_MAX; // reposition
    }
    }
    case RETURN_TO_MAX:
    {
    //using optTicks, optCid, directionFlag parameters
    int xTicks = 0; // number of ticks bot must move along x-axis
    int yTicks = 0; // number of ticks bot must move along y-axis
    int zTicks = 0; // pythagorean theorem
    int zDegrees = 0; // degrees of triangle
    
    if (directionFlag == 0) // was moving right when max sunlight detected
    {
      xTicks = (xmax - optCid - 1) * 48 - optTicks;
      if ((xmax - 1 + optCid) % 2 == 0) 
        yTicks = 0; // same edge of grid as max sunlight location
      else 
        yTicks = 48 * (ymax - 1); // opposite edge of grid
    }
    else if (directionFlag == 1) // was moving up/down when max sunlight detected
    {
      xTicks = (xmax - optCid - 1) * 48;
      if (xmax % 2 == 0) // same x-edge of origin
        yTicks = optTicks;
      else
        yTicks = 48 * (ymax - 1) - optTicks;
    }
    else
      Serial.println("ERROR: directionFlag != 0,1");

    zTicks = sqrt((xTicks^2) + (yTicks^2));

    if (yTicks == 0)
      zDegrees = 90;
    else
      zDegrees =  round( atan2 (xTicks, yTicks) * 180/3.14159265 ); // radians to degrees and rounding
      
    if (xmax % 2 == 0) 
      turnRight(180 - zDegrees); // same x-edge of origin (on the bottom)
    else
      turnLeft(180 - zDegrees); // (on the top)
      
    //moveForwardTicks(zTicks); // FIX
    
    delay(1000);
    previous_state = current_state;
    current_state = SPIN;
    }
    
    case STOP:
    {
      delay(1000);
      if(previous_state == SEARCH)
      {
        previous_state = current_state;
        current_state = SPIN;
      }
      if(previous_state == SPIN)
      {
        previous_state = current_state;
        current_state = MONITOR;
      }
    }
    case SPIN:  // RESOLUTION = 12; 132 ticks for turnRight spinning 360; 11 ticks each
    {
      int spots[12] = {};
      int spotsMax = 0;
      int i = 0; 
      int deg_id = 0;
      while(true)     // spin 360 degree
      {
        for(i = 0; i < 12; i++)
        {
          ticksL = 0; ticksR = 0;
          spots[i] = avg_ldr;
          if(spots[i] > spotsMax)
          {
            spotsMax = spots[i];
            deg_id = i;
          }
          if(ticksR < 11)
          {
            moveRight();
          }
          else
          {
            brake();
            delay(250);
            continue;
          }
        }
        break;  
      }
  
      while(true)   // spin back
      {
        if(ticksR < 11 * deg_id)
          moveRight();
        else
          break;
      }
      brake();
      delay(1000);
      previous_state = current_state;
      current_state = STOP;
    }
    case MONITOR:
    {
      while(true)
      {
        delay(20000);     // delay 20 sec for demo
        adc_vol = readSolarVoltage();
        if(adc_vol >= thresholdV)
          continue;       // continue enjoy ample sunlights here!
        else
          break;          
      }
      previous_state = current_state;
      current_state = TRACKING;  
    }
    case TRACKING:
    {
      int ldrR, ldrL;
      int diffRL = ldrL - ldrR;
      int tol = 0;  // FIX
      int deg_id = 0;
      while(true)
      {
        //ldrR = analogRead(ldrRPin);  // FIX
        //ldrL = analogRead(ldrLPin);   // FIX
        if(deg_id >= 22)  // already checked 360 degrees, should continue searching the area
        {
          previous_state = current_state;
          current_state = START;
          break;
        }
        else if (-1*tol > diffRL || diffRL > tol) // check if the diffirence is in the tolerance else change horizontal angle
        {
          ticksR = 0; ticksL = 0;
          if(ldrL > ldrR)   // left R bigger, left sunlight weaker, slightly spin right
          {
            deg_id ++;
            while(true)     // RESOLUTION = 22; 132 ticks for turnRight spinning 360; 6 ticks each
            {
              if(ticksR < 6)
                moveRight();
              else
                continue;
            }
          }
          else if(ldrL < ldrR) // right R bigger, right sunlight weaker, slightly spin left
          {
            deg_id ++;
            while(true)    
            {
              if(ticksR < 6)
                moveLeft();
              else
                continue;
            }
          }
          else if(ldrL == ldrR)
          {
          }
        }
        delay(dtime);
      }
    }
  }
}
