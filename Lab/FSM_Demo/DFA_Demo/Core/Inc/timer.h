/*
 * timer.h
 *
 *  Created on: Nov 2, 2021
 *      Author: TRAN DAT
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "main.h"
int RUNLED_counter;
uint8_t RUNLED_flag;
void setTimerRUNLED(int);

void timerRun();

#endif /* INC_TIMER_H_ */
