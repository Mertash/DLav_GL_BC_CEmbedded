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
#include "stdbool.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
	uint16_t USART3_Data_transmit[80] = {0};
	uint8_t USART3_Data_receive[1] = {0};

	uint32_t TimerClock = 0;

	uint32_t TimerButDebon = 0;

	uint8_t LED_Blue_state = 0;
	uint8_t LED_Green_state = 0;
	uint8_t LED_Orange_state = 0;
	uint8_t LED_Red_state = 0;
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
  MX_ADC1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  HAL_StatusTypeDef result;
///////////////////TEST1////////

	  /*
	  if(HAL_GetTick()-TimerClock > 1000){
	  TimerClock = HAL_GetTick();
		  HAL_UART_Transmit_IT(&huart3, "Usart3_Test\r\n", sizeof("Usart3_Test\r\n"));

	  }

	  */
//////////////////Button WORK//////////////

	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11) == 0 && HAL_GetTick()-TimerButDebon > 300){
		  TimerButDebon = HAL_GetTick();

			switch(LED_Blue_state){
			case 0:
				LED_Blue_state = 1;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, SET);
				HAL_UART_Transmit_IT(&huart3, "Blue ON\r\n", sizeof("Blue ON\r\n"));
				break;
			case 1:
				LED_Blue_state = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET);
				HAL_UART_Transmit_IT(&huart3, "Blue Off\r\n", sizeof("Blue Off\r\n"));
				break;
			}



	  	  }
	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8) == 0 && HAL_GetTick()-TimerButDebon > 300){
		  TimerButDebon = HAL_GetTick();

			switch(LED_Green_state){
			case 0:
				LED_Green_state = 1;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET);
				HAL_UART_Transmit_IT(&huart3, "Green ON\r\n", sizeof("Green ON\r\n"));
				break;
			case 1:
				LED_Green_state = 0;
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);
				HAL_UART_Transmit_IT(&huart3, "Green Off\r\n", sizeof("Green Off\r\n"));
				break;
			}
	  }


	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9) == 0 && HAL_GetTick()-TimerButDebon > 300){
	  		  TimerButDebon = HAL_GetTick();

	  			switch(LED_Orange_state){
	  			case 0:
	  				LED_Orange_state = 1;
	  				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
	  				HAL_UART_Transmit_IT(&huart3, "Orange ON\r\n", sizeof("Orange ON\r\n"));
	  				break;
	  			case 1:
	  				LED_Orange_state = 0;
	  				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);
	  				HAL_UART_Transmit_IT(&huart3, "Orange Off\r\n", sizeof("Orange Off\r\n"));
	  				break;
	  			}
	  	  }

	  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == 0 && HAL_GetTick()-TimerButDebon > 300){
				  TimerButDebon = HAL_GetTick();

					switch(LED_Red_state){
					case 0:
						LED_Red_state = 1;
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET);
						HAL_UART_Transmit_IT(&huart3, "Red ON\r\n", sizeof("Red ON\r\n"));
						break;
					case 1:
						LED_Red_state = 0;
						HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
						HAL_UART_Transmit_IT(&huart3, "Red Off\r\n", sizeof("Red Off\r\n"));
						break;
					}
			  }
//////////////////////WORK USART///////////////////
	result =  HAL_UART_Receive(&huart3, USART3_Data_receive, 2,10);

	if (result == HAL_OK){

		////Green/////
		if(USART3_Data_receive[0] == 'G' && USART3_Data_receive[1] == '1'){
			LED_Green_state = 1;
			HAL_UART_Transmit_IT(&huart3, "Green ON\r\n", sizeof("Green ON\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET);
		}

		if(USART3_Data_receive[0] == 'G' && USART3_Data_receive[1] == '0'){
			LED_Green_state = 0;
			HAL_UART_Transmit_IT(&huart3, "Green Off\r\n", sizeof("Green Off\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);

		}
		////Orange/////
		if(USART3_Data_receive[0] == 'O' && USART3_Data_receive[1] == '1'){
			LED_Orange_state = 1;
			HAL_UART_Transmit_IT(&huart3, "Orange ON\r\n", sizeof("Orange ON\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
		}
		if(USART3_Data_receive[0] == 'O' && USART3_Data_receive[1] == '0'){
			LED_Orange_state = 0;
			HAL_UART_Transmit_IT(&huart3, "Orange Off\r\n", sizeof("Orange Off\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, RESET);
		}
		////Red/////
		if(USART3_Data_receive[0] == 'R' && USART3_Data_receive[1] == '1'){
			LED_Red_state = 1;
			HAL_UART_Transmit_IT(&huart3, "Red ON\r\n", sizeof("Red ON\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, SET);
				}
		if(USART3_Data_receive[0] == 'R' && USART3_Data_receive[1] == '0'){
			LED_Red_state = 0;
			HAL_UART_Transmit_IT(&huart3, "Red Off\r\n", sizeof("Red Off\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, RESET);
			}
		////Blue/////
		if(USART3_Data_receive[0] == 'B' && USART3_Data_receive[1] == '1'){
			LED_Blue_state = 1;
			HAL_UART_Transmit_IT(&huart3, "Blue ON\r\n", sizeof("Blue ON\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, SET);
			}
		if(USART3_Data_receive[0] == 'B' && USART3_Data_receive[1] == '0'){
			LED_Blue_state = 0;
			HAL_UART_Transmit_IT(&huart3, "Blue Off\r\n", sizeof("Blue Off\r\n"));
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, RESET);
			}


	}



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }

  void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){


	 if (huart == &huart3 ){

		 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, SET);
		  if(USART3_Data_receive == "DED"){
			  LED_Green_state = 1;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, SET);
			//HAL_UART_Transmit_IT(&huart3, "Green ON\r\n", sizeof("Green ON\r\n"));
		  }

		  if(USART3_Data_receive == "Green_turnOff"){
			  LED_Green_state = 0;
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, RESET);
			HAL_UART_Transmit_IT(&huart3, "Green Off\r\n", sizeof("Green Off\r\n"));
		  }

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
  RCC_OscInitStruct.PLL.PLLN = 84;
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
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_9;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_112CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
