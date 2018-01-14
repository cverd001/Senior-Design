


#define START 0
#define STOP 1
#define SPIN 2
#define SEARCH 3
#define MONITOR 4
#define RETURN_TO_MAX 5

int maxSolarV = 14;
int adc_vol = 0;      // adc reading
int avg_r = 0;    // photoresistors average reading
int x, y;       // grid cordinates
int xmax, ymax;
int current_state = 0, previous_state = 0;
const int adc_threshold = 0;  // set threshold
const int r_threshold = 0;

void searching()
{
	//initialize
	current_state = START;

	switch(current_state)
<<<<<<< HEAD
	case START: 
	{
		x = 0; y = 0;
		previous_state = current_state;
		current_state = SEARCH;
	}
	case SEARCH:
	{
	  // xmax, ymax are grid definitions: e.g. 5x5
	  // threshold parameter
    int xpos = 0;
    int ypos = 0;
    updown = 3; //flag to check if robot was moving up/down or left/right when max sunlight was acquired. If updown is not 0 or 1 when checked results in error.
    stopFlag = 0;
    numTicks = 0;
    numCid = 0;
    for (int Cid = 0; Cid < xmax; Cid++)
=======
  {
  	case START: 
>>>>>>> 78a1ae3d5cb9f7ab263c709fc2ce470b7e93ad68
    {
      x = 0; y = 0;
      delay(500);
      previous_state = current_state;
      current_state = SEARCH;
    }
  	case SEARCH:
  	{
      // xmax, ymax are grid definitions: e.g. 5x5
      // threshold parameter
      int xpos = 0;
      int ypos = 0;
      int stopFlag = 0;
      int numTicks = 0;
      int numCid = 0;
      for (int Cid = 0; Cid < xmax; Cid++)
      {
          int ticks = ymax * 30 * 1.6;  //1.6 ticks per cm
          moveForward();
          delay(20);
          ticksL = 0;
          ticksR = 0;
          while (true)
          {
            delay(1);
            if (ticksR % 8 == 0) // take reading every 5cm
            {
<<<<<<< HEAD
              maxSolarV = temp;
              numTicks = (pulse_left + pulse_right) / 2;
              numCid = Cid;
              if (Cid % 2 == 1)
                numTicks = ticks - numTicks; //maxTicks - tick number when bot is going down instead of up
              updown = 1; //flag, bot was moving up/down
=======
              int adc_vol = readSolarVoltage(); // FIX
              if (adc_vol > maxSolarV)
              {
                maxSolarV = adc_vol;
                numTicks = (ticksL + ticksR) / 2;
                numCid = Cid;
              }
              if (maxSolarV >= adc_threshold)
              {
                stopFlag = 1; // signals that max threshold has been reached
                break;
              }
>>>>>>> 78a1ae3d5cb9f7ab263c709fc2ce470b7e93ad68
            }
            if (ticksR >= ticks && ticksL >= ticks)
              break;    
             
          }
          brake();
          if (stopFlag)
            break;
          if (Cid % 2 == 0) // if even, turn left
            turnRight(90);
          else
            turnLeft(90);
          // Move forward 1 grid space
          moveForward();
          delay(20);
          ticksL = 0;
          ticksR = 0;
          while (true)
          {
            delay(1);
            if (ticksR % 8 == 0) // take reading every 5cm
            {
              int adc_vol = readSolarVoltage(); // FIX
              if (adc_vol > maxSolarV)
              {
                maxSolarV = adc_vol;
                numTicks = (ticksL + ticksR) / 2;
                numCid = Cid;
              }
              if (maxSolarV >= adc_threshold)
              {
                stopFlag = 1; // signals that max threshold has been reached
                break;
              }
            }
            if (ticksR >= 48 && ticksL >= 48) // 1 grid space
              break;    
          }
<<<<<<< HEAD
          if (pulse_right >= ticks && pulse_left >= ticks)
            break;    
           
        }
        brake();
        if (stopFlag)
          break;
        if (Cid % 2 == 0) // if even, turn left
          turnRight(90);
        else
          turnLeft(90);
        // Move forward 1 grid space
        moveForward();
        delay(20);
        pulse_left = 0;
        pulse_right = 0;
        while (true) // check while moving 1 grid space right
=======
          brake();
          if (stopFlag)
            break;
          if (Cid % 2 == 0) // if even, turn right
            turnRight(90);
          else
            turnLeft(90);
          
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
>>>>>>> 78a1ae3d5cb9f7ab263c709fc2ce470b7e93ad68
        {
          ticksL = 0; ticksR = 0;
          spots[i] = avg_r;
          if(spots[i] > spotsMax)
          {
<<<<<<< HEAD
            int temp = readSolarVoltage(); // FIX
            if (temp > maxSolarV)
            {
              maxSolarV = temp;
              numTicks = (pulse_left + pulse_right) / 2; // how many ticks to the right of Cid
              numCid = Cid;
              updown = 0;
            }
            if (maxSolarV >= thresholdV)
            {
              stopFlag = 1; // signals that max threshold has been reached
              break;
            }
=======
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
>>>>>>> 78a1ae3d5cb9f7ab263c709fc2ce470b7e93ad68
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
<<<<<<< HEAD
    else
    {
      current_state = RETURN_TO_MAX; // reposition
    }
	}
	case RETURN_TO_MAX:
	{
    //numTicks, numCid
    if (updown == 0) // was moving right when max sunlight detected
    {
      int xTicks = (xmax - numCid - 1) * 48 - numTicks;
      if ((xmax - 1 + numCid) % 2 == 0) // same edge of grid as max sunlight location
        int yTicks = 0;
      else 
        int yTicks = 48 * (ymax - 1); //opposite edge of grid
    }
    else if (updown == 1) // was moving up/down when max sunlight detected
    {
      int xTicks = (xmax - numCid - 1) * 48;
      if (xmax % 2 == 0) // same x-edge of origin
        int yTicks = numTicks;
      else
        int yTicks = 48 * (ymax - 1) - numTicks;
    }
    else
      Serial.println("ERROR: updown != 0,1");

    int zTicks = sqrt(xTicks^2 + yTicks^2);
    int zDegrees;
    if (yTicks == 0)
      zDegrees = 90;
    else
      zDegrees =  round( atan2 (xTicks, yTicks) * 180/3.14159265 ); // radians to degrees and rounding
      
    if (xmax % 2 == 0) // same x-edge of origin
      turnRight(180 - zDegrees);
    else
      turnLeft(180 - zDegrees);
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
	case SPIN:
	{
		while(true)
		{
			ticksL = 0;
			ticksR = 0;
			angle = angleCalculation(int ticksL, int ticksR);
			avg_left = analogRead(left_a) + analogRead(left_b);
			avg_right = analogRead(right_a) + analogRead(right_b);
			diff_ldr = avg_right - avg_left;

			if(diff_ldr > tolerance)	// should spin left, light: left > right
			{
				moveLeft();
				delay(100);
				continue
			}
			if(diff_ldr < -1*tolerance)
			{
				moveRight();
				delay(100);
				continue
			}
			else	// already find a proper angle, could stop
			{
				previous_state = current_state;
				current_state = STOP;
				break;
			}
		}
	}
	case MONITOR:
	{
		if()
	}
=======
  	case MONITOR:
  	{
  		while(true)
      {
        delay(20000);     // delay 20 sec for demo
        adc_vol = readSolarVoltage();
        if(adc_vol >= adc_threshold)
          continue;       // continue enjoy ample sunlights here!
        else
          break;          
      }
      previous_state = current_state;
      current_state = START;  
  	}
  }
>>>>>>> 78a1ae3d5cb9f7ab263c709fc2ce470b7e93ad68
}




