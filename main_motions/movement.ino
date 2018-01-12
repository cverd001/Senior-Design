/*


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
		/*




	if(avg_ldr < set_threshold)
			previous_state = current_state;
			current_state = STOP;
		else 
			continue
		//go to detailed searching loop
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


*/

