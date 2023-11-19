/*
 * timer.h
 *
 *  Created on: Nov 2, 2021
 *      Author: TRAN DAT
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_
#include "main.h"
#include "input_reading.h"

void setTimer7SegLED(int);
void setTimerTrafficLED(int);
void setTimerLedBlinking(int);
void timer_run();

uint8_t timer7SegLED_FLAG();
uint8_t timerTrafficLED_FLAG();
uint8_t timerLedBlinking_FLAG();



#endif /* INC_TIMER_H_ */