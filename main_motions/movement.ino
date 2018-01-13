


#define START 0
#define STOP 1
#define SPIN 2
#define SEARCH 3
#define MONITOR 4
#define RETURN_TO_MAX 5

int adc_vol = 0;      // adc reading
int avg_ldr = 0;    // photoresistors average reading
int x, y;       // grid cordinates
int current_state = 0, previous_state = 0;
const int adc_threshold;  // set threshold
const int r_threshold;

void searching()
{
	//initialize
	current_state = START;

	switch(current_state)
	case START: 
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
    stopFlag = 0;
    numTicks = 0;
    numCid = 0;
    for (int Cid = 0; Cid < xmax; Cid++)
    {
        int ticks = ymax * 30 * 1.6;  //1.6 ticks per cm
        moveForward();
        delay(20);
        pulse_left = 0;
        pulse_right = 0;
        while (true)
        {
          delay(1);
          if (pulse_right % 8 == 0) // take reading every 5cm
          {
            int temp = readSolarVoltage(); // FIX
            if (temp > maxSolarV)
            {
              maxSolarV = temp;
              numTicks = (pulse_left + pulse_right) / 2;
              numCid = Cid;
            }
            if (maxSolarV >= thresholdV)
            {
              stopFlag = 1; // signals that max threshold has been reached
              break;
            }
          }
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
        while (true)
        {
          delay(1);
          if (pulse_right % 8 == 0) // take reading every 5cm
          {
            int temp = readSolarVoltage(); // FIX
            if (temp > maxSolarV)
            {
              maxSolarV = temp;
              numTicks = (pulse_left + pulse_right) / 2;
              numCid = Cid;
            }
            if (maxSolarV >= thresholdV)
            {
              stopFlag = 1; // signals that max threshold has been reached
              break;
            }
          }
          if (pulse_right >= 48 && pulse_left >= 48) // 1 grid space
            break;    
        }
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
    int max = 0;
    int i = 0; 
    int deg_id = 0;
    while(true)     // spin 360 degree
    {
      for(i = 0; i < 12; i++)
      {
        ticksL = 0; ticksR = 0;
        spots[i] = avg_r;
        if(spots[i] > max)
        {
          max = spots[i];
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
      if(adc_vol >= adc_threshold)
        continue;       // continue enjoy ample sunlights here!
      else
        break;          
    }
    previous_state = current_state;
    current_state = START;  
	}
}




