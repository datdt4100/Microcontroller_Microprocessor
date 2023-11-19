/*
 * timer.c
 *
 *  Created on: Nov 2, 2021
 *      Author: TRAN DAT
 */
#include "timer.h"

const int CYCLE_PERIOD = 10;

void setTimerRUNLED(int duration)
{
	RUNLED_counter = duration / CYCLE_PERIOD;
	RUNLED_flag = 0;
}

void timerRun()
{
	if (RUNLED_counter > 0)
	{
		RUNLED_counter --;
		if (RUNLED_counter == 0)
			RUNLED_flag = 1;
	}
}

