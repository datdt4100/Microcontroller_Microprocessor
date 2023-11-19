/*
 * input_processing.c
 *
 *  Created on: Nov 2, 2021
 *      Author: TRAN DAT
 */
#include "input_processing.h"
enum SystemState
{
	STOP,
	RUN,
	PAUSE
};

enum SystemState State = STOP;
void FSM_Btn()
{
	switch(State)
	{
	case STOP:
		if (is_pressed(1))
		{
			while (is_pressed(1));
			State = RUN;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, SET);
		}
		break;
	case RUN:
		if (is_pressed(1))
		{
			while (is_pressed(1));
			State = PAUSE;
		}
		else if (is_pressed(0))
		{
			while (is_pressed(0));
			State = STOP;
		}
		else
		{
			if (RUNLED_flag == 1)
			{
				HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
				setTimerRUNLED(250);
			}
		}
		break;
	case PAUSE:
		if (is_pressed(1))
		{
			while (is_pressed(1));
			State = RUN;
		}
		else if (is_pressed(0))
		{
			while (is_pressed(0));
			State = STOP;
		}
		else
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, RESET);
		}
		break;
	}
}