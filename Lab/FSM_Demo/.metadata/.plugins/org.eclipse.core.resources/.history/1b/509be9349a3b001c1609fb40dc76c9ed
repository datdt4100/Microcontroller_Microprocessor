/*
 * input_reading.c
 *
 *  Created on: Nov 2, 2021
 *      Author: TRAN DAT
 */
#include "input_reading.h"

static GPIO_PinState buttonBuffer [N_BUTTONS];
// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1 [ N_BUTTONS ];
static GPIO_PinState debounceButtonBuffer2 [ N_BUTTONS ];

void button_reading()
{
	for ( char i = 0; i < N_BUTTONS ; i ++){
		debounceButtonBuffer2 [i] = debounceButtonBuffer1 [i];
		debounceButtonBuffer1 [i] = HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_2 << i);
		if( debounceButtonBuffer1 [i] == debounceButtonBuffer2 [i])
			buttonBuffer [i] = debounceButtonBuffer1 [i];
	}
}
uint8_t is_pressed ( uint8_t idx ){

	assert_param(IS_IDX_BUTTON(idx));

	return ( buttonBuffer [ idx ] == IS_PRESSED );
}

