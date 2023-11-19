/*
 * timer.c
 *
 *  Created on: Nov 2, 2021
 *      Author: TRAN DAT
 */
#include "timer.h"

int timer7SegLED_counter = 0;
int timerTrafficLED_counter = 0;
int timerLedBlinking_counter = 0;

uint8_t timer7SegLED_flag = 0;
uint8_t timerTrafficLED_flag = 0;
uint8_t timerLedBlinking_flag = 0;

int TIMER_CYCLE = 10;

void setTimer7SegLED(int duration)
{
	timer7SegLED_counter = duration/TIMER_CYCLE;
	timer7SegLED_flag = 0;
}

void setTimerTrafficLED(int duration)
{
	timerTrafficLED_counter = duration/TIMER_CYCLE;
	timerTrafficLED_flag = 0;
}

void setTimerLedBlinking(int duration)
{
	timerLedBlinking_counter = duration/TIMER_CYCLE;
	timerLedBlinking_flag = 0;
}

void timer_run()
{
	if (timer7SegLED_counter > 0)
	{
		timer7SegLED_counter--;
		if (timer7SegLED_counter == 0)
			timer7SegLED_flag = 1;
	}

	if (timerTrafficLED_counter > 0)
	{
		timerTrafficLED_counter--;
		if (timerTrafficLED_counter == 0){
			timerTrafficLED_flag = 1;
		}
	}

	if (timerLedBlinking_counter > 0)
	{
		timerLedBlinking_counter--;
		if (timerLedBlinking_counter == 0)
		{
			timerLedBlinking_flag = 1;
		}
	}
}

uint8_t timer7SegLED_FLAG()
{
	return timer7SegLED_flag;
}
uint8_t timerTrafficLED_FLAG()
{
	return timerTrafficLED_flag;
}
uint8_t timerLedBlinking_FLAG()
{
	return timerLedBlinking_flag;
}
