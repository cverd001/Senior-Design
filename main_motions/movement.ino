


#define START 0
#define STOP 1
#define SPIN 2
#define SEARCH 3
#define MONITOR 4
#define RETURN_TO_MAX 5

void searching()
{
	//initialize
	current_state = START;

	switch(current_state)
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
      current_state = STOP;
    }
    else
    {
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
}




