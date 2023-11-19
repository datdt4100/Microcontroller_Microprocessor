/*
 * traffic_light_sys.c
 *
 *  Created on: Nov 10, 2021
 *      Author: TRAN DAT
 */
#include "traffic_light_sys.h"

typedef enum LIGHT_STATE {
	RED,
	AMBER,
	GREEN
} trafficLightState_t;

static trafficLightState_t CURR_STATE[2];


typedef enum SYS_STATE
{
	NORMAL,
	MODIFY_LED_RED,
	CONFIRM_RED,
	MODIFY_LED_YELLOW,
	CONFIRM_YELLOW
} state_t;

static state_t MODE;

static char TIME_RED = 9;
static char TIME_AMBER = 3;
static char TIME_GREEN = 5;

uint8_t timeBuffer[2];

int idxLED = 0;

static int8_t TIME[2];

uint8_t LED7SEG_BUFFER[2][2] = {{0x08, 0x08}, {0x08, 0x08}};
uint16_t LED_Cathod[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
void Traffic_Init()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
		                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);
	MODE = NORMAL;
	setTimer7SegLED(50);
	setTimerTrafficLED(50);
	CURR_STATE[0] = RED;
	CURR_STATE[1] = GREEN;
	TIME[0] = TIME_RED;
	TIME[1] = TIME_GREEN = TIME_RED - TIME_AMBER - 1;
	Led7SegBuffer_update();
}
void traffic_update()
{
	for (int i = 0; i < 2; i ++){
		switch (CURR_STATE[i])
		{
		case RED:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 << (i * 3), RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 << (i * 3), SET);
			if (--TIME[i] == -1)
			{
				CURR_STATE[i] = GREEN;
				TIME[i] = TIME_GREEN;
			}
			break;
		case GREEN:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 << (i * 3), RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 << (i * 3), SET);
			if (--TIME[i] == -1)
			{
				CURR_STATE[i] = AMBER;
				TIME[i] = TIME_AMBER;
			}
			break;
		case AMBER:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 << (i * 3), RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4 << (i * 3), SET);
			if (--TIME[i] == -1)
			{
				CURR_STATE[i] = RED;
				TIME[i] = TIME_RED;
			}
			break;
		}

	}
}

void Led7SegBuffer_update()
{
	LED7SEG_BUFFER[1][0] = TIME[0] / 10;
	LED7SEG_BUFFER[1][1] = TIME[0] % 10;

	LED7SEG_BUFFER[0][0] = TIME[1] / 10;
	LED7SEG_BUFFER[0][1] = TIME[1] % 10;
}

void Led7Seg_update(int idx)
{
	GPIOA->BSRR = GPIO_PIN_11 << (idx + 16) | GPIO_PIN_11 << (1-idx);
	uint16_t bits = (LED_Cathod[LED7SEG_BUFFER[1][idx]] << 7u) | (LED_Cathod[LED7SEG_BUFFER[0][idx]]);
	GPIOB->BSRR = (uint32_t)bits << 16u | (~bits << 2u >> 2u);
}

void fsm_input_button()
{
	switch (MODE)
	{
	case NORMAL:
		if (timerTrafficLED_FLAG() == 1)
		{
			Led7SegBuffer_update();
			traffic_update();
			setTimerTrafficLED(950);
		}
		if (is_pressed(0))
		{
			while (is_pressed(0))
				continue;
			MODE = MODIFY_LED_RED;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
					                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);
			timeBuffer[0] = TIME_RED;
			setTimerLedBlinking(250);
			setTimerTrafficLED(10000);
		}
		break;
	case MODIFY_LED_RED:
		LED7SEG_BUFFER[0][0] = 0;
		LED7SEG_BUFFER[0][1] = 1;
		LED7SEG_BUFFER[1][0] = timeBuffer[0] / 10;
		LED7SEG_BUFFER[1][1] = timeBuffer[0] % 10;
		if (timerLedBlinking_FLAG() == 1)
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_5);
			setTimerLedBlinking(250);
		}

		if (is_pressed(1))
		{
			while (is_pressed(1))
				continue;
			timeBuffer[0] += 1;
			if (timeBuffer[0] > 99)
				timeBuffer[0] = 1;
			setTimerTrafficLED(10000);
		}
		else if (is_pressed(2))
		{
			while (is_pressed(2))
				continue;
			timeBuffer[0] -= 1;
			if (timeBuffer[0] == 0)
				timeBuffer[0] = 99;
			setTimerTrafficLED(10000);
		}
		else if (is_pressed(0))
		{
			while (is_pressed(0))
				continue;
			MODE = CONFIRM_RED;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_5, RESET);
			setTimerTrafficLED(10000);
		}

		if (timerTrafficLED_FLAG() == 1)
		{
			Traffic_Init();
		}
		break;
	case CONFIRM_RED:
		LED7SEG_BUFFER[0][0] = 0;
		LED7SEG_BUFFER[0][1] = 2;
		if (is_pressed(1))
		{
			while (is_pressed(1))
				continue;
			MODE = MODIFY_LED_YELLOW;
			TIME_RED = timeBuffer[0];
			timeBuffer[1] = TIME_AMBER;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2 | GPIO_PIN_5, SET);
			setTimerTrafficLED(10000);
		}
		else if (is_pressed(2))
		{
			while (is_pressed(2))
				continue;
			MODE = MODIFY_LED_RED;
			setTimerTrafficLED(10000);
		}


		if (timerTrafficLED_FLAG() == 1)
		{
			Traffic_Init();
		}
		break;
	case MODIFY_LED_YELLOW:
		LED7SEG_BUFFER[0][0] = 0;
		LED7SEG_BUFFER[0][1] = 3;
		LED7SEG_BUFFER[1][0] = 0;
		LED7SEG_BUFFER[1][1] = timeBuffer[1];
		if (timerLedBlinking_FLAG() == 1)
		{
			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_6);
			setTimerLedBlinking(250);
		}
		if (is_pressed(1))
		{
			while (is_pressed(1))
				continue;
			timeBuffer[1] += 1;
			if (timeBuffer[1] > 5)
				timeBuffer[1] = 1;
			setTimerTrafficLED(10000);
		}
		else if (is_pressed(2))
		{
			while (is_pressed(2))
				continue;
			timeBuffer[1] -= 1;
			if (timeBuffer[1] == 0)
				timeBuffer[1] = 5;
			setTimerTrafficLED(10000);
		}
		else if (is_pressed(0))
		{
			while (is_pressed(0))
				continue;
			MODE = CONFIRM_YELLOW;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3 | GPIO_PIN_6, RESET);
			setTimerTrafficLED(10000);
		}

		if (timerTrafficLED_FLAG() == 1)
		{
			Traffic_Init();
		}
		break;
	case CONFIRM_YELLOW:
		LED7SEG_BUFFER[0][0] = 0;
		LED7SEG_BUFFER[0][1] = 4;
		if (is_pressed(1))
		{
			while (is_pressed(1))
				continue;
			MODE = NORMAL;
			setTimer7SegLED(50);
			setTimerTrafficLED(50);
			setTimerLedBlinking(0);
			CURR_STATE[0] = RED;
			CURR_STATE[1] = GREEN;

			TIME_AMBER = timeBuffer[1];
			TIME[0] = TIME_RED;
			TIME[1] = TIME_GREEN = TIME_RED - TIME_AMBER - 1;
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
					                          |GPIO_PIN_6|GPIO_PIN_7, GPIO_PIN_SET);
		}
		else if (is_pressed(2))
		{
			while (is_pressed(2))
				continue;
			MODE = MODIFY_LED_YELLOW;
			setTimerTrafficLED(10000);
		}

		if (timerTrafficLED_FLAG() == 1)
		{
			Traffic_Init();
		}
		break;
	}
	if (timer7SegLED_FLAG() == 1)
	{
		Led7Seg_update(idxLED);
		idxLED = (idxLED == 0);
		setTimer7SegLED(250);
	}
}

