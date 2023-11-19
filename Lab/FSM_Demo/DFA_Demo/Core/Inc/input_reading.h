/*
 * input_reading.h
 *
 *  Created on: Nov 2, 2021
 *      Author: TRAN DAT
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"

#define N_BUTTONS	2

#define IS_IDX_BUTTON(IDX)	((uint8_t)IDX >= 0 && (uint8_t)IDX < N_BUTTONS)

#define IS_PRESSED	GPIO_PIN_RESET
#define IS_RELEASED	GPIO_PIN_SET

void button_reading();
uint8_t is_pressed(uint8_t);

#endif /* INC_INPUT_READING_H_ */
