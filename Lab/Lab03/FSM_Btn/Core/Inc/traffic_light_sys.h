/*
 * traffic_light_sys.h
 *
 *  Created on: Nov 10, 2021
 *      Author: TRAN DAT
 */

#ifndef INC_TRAFFIC_LIGHT_SYS_H_
#define INC_TRAFFIC_LIGHT_SYS_H_
#include "timer.h"
#include "main.h"

#define RED_TIME_MAX	99
#define YELLOW_TIME_MAX	5

void Traffic_Init();
void traffic_update();
void Led7SegBuffer_update();
void Led7Seg_update(int);
void fsm_input_button();

#endif /* INC_TRAFFIC_LIGHT_SYS_H_ */
