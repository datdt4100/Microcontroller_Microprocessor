/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define IS_LED7SEG_VALUE(VALUE) (VALUE > -1 && VALUE < 10)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
const int MAX_LED = 4;
int index_led = 0;
static char led_buffer[4] = {1, 2, 3, 0};
int hour = 23, minute = 03, second = 0;
char count = 0;
//int LED = 5;
int ledIndex = 0;

int timer0_counter = 0;
int timer0_flag = 0;

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

int timer3_counter = 0;
int timer3_flag = 0;

int TIMER_CYCLE = 10;

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer [8] = {0x18 , 0x3C , 0x66 , 0x66 , 0x7E , 0x7E , 0x66 , 0x66 };
uint8_t matrix [14][8] = {	{0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 },

							{0x00 , 0x00 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 , 0x80 },
							{0x00 , 0x80 , 0xC0 , 0xC0 , 0xC0 , 0xC0 , 0xC0 , 0xC0 },
							{0x80 , 0xC0 , 0x60 , 0x60 , 0xE0 , 0xE0 , 0x60 , 0x60 },
							{0xC0 , 0xE0 , 0x30 , 0x30 , 0xF0 , 0xF0 , 0x30 , 0x30 },
							{0x60 , 0xF0 , 0x98 , 0x98 , 0xF8 , 0xF8 , 0x98 , 0x98 },
							{0x30 , 0x78 , 0xCC , 0xCC , 0xFC , 0xFC , 0xCC , 0xCC },

							{0x18 , 0x3C , 0x66 , 0x66 , 0x7E , 0x7E , 0x66 , 0x66 },

							{0x0C , 0x1E , 0x33 , 0x33 , 0x3F , 0x3F , 0x33 , 0x33 },
							{0x06 , 0x0F , 0x19 , 0x19 , 0x1F , 0x1F , 0x19 , 0x19 },
							{0x03 , 0x07 , 0x0C , 0x0C , 0x0F , 0x0F , 0x0C , 0x0C },
							{0x01 , 0x03 , 0x06 , 0x06 , 0x07 , 0x07 , 0x06 , 0x06 },
							{0x00 , 0x01 , 0x03 , 0x03 , 0x03 , 0x03 , 0x03 , 0x03 },
							{0x00 , 0x00 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 , 0x01 }};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_TIM2_Init(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
void display7SEG(int);
void update7SEG (int);
void updateClockBuffer();
void setTimer0(int);
void setTimer1(int);
void setTimer2(int);
void setTimer3(int);
void timer_run();

void updateLEDMatrix(int, int);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_TIM2_Init();
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0(10);
  setTimer1(10);
  setTimer2(10);
  setTimer3(10);
  int animation = 7;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
/*
	  if (timer0_flag == 1)
	  {
		  second ++;
		  if (second > 59){
			  second = 0;
			  minute++;
		  }
		  if (minute > 59){
			  minute = 0;
			  hour++;
		  }
		  if (hour > 23){
			  hour = 0;
		  }
		  updateClockBuffer ();
		  setTimer0(1000);
	  }
	  if (timer1_flag == 1)
	  {
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
		  setTimer1(500);
	  }
	  if (timer2_flag == 1)
	  {
		  if (ledIndex == 4) ledIndex = 0;
		  update7SEG(ledIndex++);
		  setTimer2(250);
	  }
*/
	  if (timer3_flag == 1)
	  {
		  if (index_led_matrix == MAX_LED_MATRIX) {
			  index_led_matrix = 0;
			  if (++animation == 14) animation = 0;
		  }

		  updateLEDMatrix(index_led_matrix++, animation);
		  setTimer3(100);
	  }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA1 PA2 PA3 PA4
                           PA5 PA6 PA7 PA8
                           PA9 PA10 PA11 PA12
                           PA13 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB3 PB4 PB5 PB6
                           PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void display7SEG(int NUM)
{
	assert_param(IS_LED7SEG_VALUE(NUM));
	uint16_t LED_Cathod[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};
	GPIOB->BSRR =  (uint32_t)((LED_Cathod[NUM]) << 16) | (~LED_Cathod[NUM]);
}

void updateClockBuffer()
{
	led_buffer[0] = hour / 10;
	led_buffer[1] = hour % 10;
	led_buffer[2] = minute / 10;
	led_buffer[3] = minute % 10;
}
void update7SEG (int index)
{
	//GPIOA->BSRR = (uint32_t)(1 << (22 + index)) | ~(~(GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9) | (1 << (index + 6)));
	//display7SEG(led_buffer[index]);
	switch (index)
	{
	case 0:
		GPIOA->BSRR = (uint32_t)GPIO_PIN_10 << 16 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 ;
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		display7SEG(led_buffer[index]);
		break;
	case 1:
		GPIOA->BSRR = (uint32_t)GPIO_PIN_11 << 16 | GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_13 ;
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
		display7SEG(led_buffer[index]);
		break;
	case 2:
		GPIOA->BSRR = (uint32_t)GPIO_PIN_12 << 16 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_13 ;
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9, GPIO_PIN_SET);
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
		display7SEG(led_buffer[index]);
		break;
	case 3:
		GPIOA->BSRR = (uint32_t)GPIO_PIN_13 << 16 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 ;
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8, GPIO_PIN_SET);
		//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
		display7SEG(led_buffer[index]);
		break;
	default:
		break;
	}
}



void updateLEDMatrix (int index, int time ){
	/*
	switch(index)
	{
	case 0:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_7 << 16 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 1:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_8 << 16 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 2:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_9 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 3:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_10 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 4:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_11 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 5:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_12 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 6:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_13 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14;
		break;
	case 7:
		GPIOA->BSRR = (uint32_t)matrix_buffer[index] << 17 | ((uint16_t)(~matrix_buffer[index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_14 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
		break;
	default:
		break;
	}
	*/
	switch(index)
	{
	case 0:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_7 << 16 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 1:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_8 << 16 | GPIO_PIN_7 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 2:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_9 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 3:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_10 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 4:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_11 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 5:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_12 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14;
		break;
	case 6:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_13 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14;
		break;
	case 7:
		GPIOA->BSRR = (uint32_t)matrix[time][index] << 17 | ((uint16_t)(~matrix[time][index]) << 8 >> 7);
		GPIOB->BSRR = (uint32_t)GPIO_PIN_14 << 16 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
		break;
	default:
		break;
	}
}

void setTimer0 ( int duration )
{
	timer0_counter = duration / TIMER_CYCLE ;
	timer0_flag = 0;
}

void setTimer1 ( int duration )
{
	timer1_counter = duration / TIMER_CYCLE ;
	timer1_flag = 0;
}

void setTimer2 ( int duration )
{
	timer2_counter = duration / TIMER_CYCLE ;
	timer2_flag = 0;
}

void setTimer3 ( int duration )
{
	timer3_counter = duration / TIMER_CYCLE ;
	timer3_flag = 0;
}

void timer_run ()
{

	if( timer0_counter > 0){
		timer0_counter--;
		if( timer0_counter == 0) timer0_flag = 1;
	}
	if( timer1_counter > 0){
		timer1_counter--;
		if( timer1_counter == 0) timer1_flag = 1;
	}
	if( timer2_counter > 0){
		timer2_counter--;
		if(timer2_counter == 0) timer2_flag = 1;
	}
	if( timer3_counter > 0){
		timer3_counter --;
		if(timer3_counter == 0) timer3_flag = 1;
	}
}

void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef * htim )
{
	timer_run();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/