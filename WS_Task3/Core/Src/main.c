/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#define DUTY_CH1 CCR1
#define DUTY_CH2 CCR2
#define DUTY_CH3 CCR3
#define DUTY_CH4 CCR4

#define CH_CANGE_BUTTON_PIN GPIO_PIN_15 //ON_OFF_BUTTON_PIN
#define DUTY_UP_BUTTON_PIN GPIO_PIN_11 //NEXT_BUTTON_PIN
#define DUTY_DOWN_BUTTON_PIN GPIO_PIN_9//PREV_BUTTON_PIN
#define FREQ_UP_BUTTON_PIN GPIO_PIN_6 //SPEED_UP_BUTTON_PIN
#define FREQ_DOWN_BUTTON_PIN GPIO_PIN_8//SPEED_DOWN_BUTTON_PIN

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


volatile uint16_t PWM_PERIOD = 40000;
volatile uint16_t PWM_PERIOD_5kHZ_STEP = 3250;
volatile uint16_t PWM_PERIOD_MAX = 65000;
volatile uint16_t PWM_PERIOD_MIDDLE = 32500;
volatile uint16_t PWM_PERIOD_MIN = 0;

uint16_t PWM_DUTY_CURENT_CH_ALL = 20000;
uint16_t PWM_DUTY_MAX;
uint16_t PWM_DUTY_MIDDLE;
uint16_t PWM_DUTY_MIN = 0;
uint16_t PWM_DUTY_5PCT_STEP;

uint8_t CURRENT_SCHEME = 0;

uint32_t LAST_TICK = 0;

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
  MX_GPIO_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  	//////////init variables//////////

	  	TIM4->ARR = PWM_PERIOD;
	  	PWM_DUTY_MAX = PWM_PERIOD;
	  	PWM_DUTY_5PCT_STEP = PWM_PERIOD/20;
	  	PWM_DUTY_MIDDLE = PWM_PERIOD/2;

	  	////////////////////////

			  if(CURRENT_SCHEME == 0){

				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
			  }
			  if (CURRENT_SCHEME == 1){

				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
				  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
				  TIM4->CCR1=PWM_DUTY_CURENT_CH_ALL;
			  }
			  if(CURRENT_SCHEME == 2){

				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
				  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
				  TIM4->CCR2=PWM_DUTY_CURENT_CH_ALL;
			  }
			  if(CURRENT_SCHEME == 3){

				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_4);
				  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
				  TIM4->CCR3=PWM_DUTY_CURENT_CH_ALL;
			  }
			  if(CURRENT_SCHEME == 4){

				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
				  HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
				  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
				  TIM4->CCR4=PWM_DUTY_CURENT_CH_ALL;
			  }



			if((HAL_GetTick()- LAST_TICK) >=500)
			{	LAST_TICK = HAL_GetTick();

				if(HAL_GPIO_ReadPin(GPIOC, DUTY_UP_BUTTON_PIN) == 0) {
					if(PWM_DUTY_CURENT_CH_ALL < PWM_PERIOD_MAX){
						PWM_DUTY_CURENT_CH_ALL += PWM_DUTY_5PCT_STEP;
					}

				}
				else if(HAL_GPIO_ReadPin(GPIOC, DUTY_DOWN_BUTTON_PIN) == 0) {
					if(PWM_DUTY_CURENT_CH_ALL > PWM_PERIOD_MIN) {
						PWM_DUTY_CURENT_CH_ALL -= PWM_DUTY_5PCT_STEP;
					}
				}
				else if(HAL_GPIO_ReadPin(GPIOC, FREQ_UP_BUTTON_PIN) == 0) {
					if(PWM_PERIOD > PWM_PERIOD_MIN) {
						PWM_PERIOD -= PWM_PERIOD_5kHZ_STEP;
					}
				}
				else if(HAL_GPIO_ReadPin(GPIOC, FREQ_DOWN_BUTTON_PIN) == 0) {
					if(PWM_PERIOD < PWM_PERIOD_MAX) {
						PWM_PERIOD += PWM_PERIOD_5kHZ_STEP;
					}
				}
				else if(HAL_GPIO_ReadPin(GPIOA, CH_CANGE_BUTTON_PIN) == 0) {
						CURRENT_SCHEME = (CURRENT_SCHEME + 1) % 5;

						if(CURRENT_SCHEME == 5){CURRENT_SCHEME = 0;}
				}

			}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 80;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1000;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 40000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pins : PC6 PC8 PC9 PC11 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

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
