/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */
HAL_StatusTypeDef status;

CAN_TxHeaderTypeDef AccelHeader = {
    .StdId = ACCEL_MESSAGE_ID,
    .IDE = CAN_ID_STD,
    .RTR = CAN_RTR_DATA,
    .DLC = 6
};
uint8_t AccelData[6] = {0};

CAN_TxHeaderTypeDef GyroHeader = {
    .StdId = GYRO_MESSAGE_ID,
    .IDE = CAN_ID_STD,
    .RTR = CAN_RTR_DATA,
    .DLC = 6
};
uint8_t GyroData[6] = {0};

uint32_t Mailbox;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

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
  // // Enable GPIOF clock
  // RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
  // RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

  // // PF0 and PF1 as general-purpose outputs (MODER = 01)
  // GPIOA->MODER &= ~(3U << (10 * 2)); // clear mode bits
  // GPIOA->MODER |=  (1U << (10 * 2)); // set to output
  // GPIOB->MODER &= ~(3U << (8 * 2)); // clear mode bits
  // GPIOB->MODER |=  (1U << (8 * 2)); // set to output

  // // Push-pull outputs (OTYPER = 0)
  // GPIOA->OTYPER &= ~(1U << 10);
  // GPIOB->OTYPER &= ~(1U << 8);

  // // No pull-up/pull-down
  // GPIOA->PUPDR &= ~(3U << (10 * 2));
  // GPIOB->PUPDR &= ~(3U << (8 * 2));

  // while (1)
  // {
  //   // Drive both pins LOW
  //   GPIOA->ODR &= ~(1U << 10);
  //   GPIOB->ODR &= ~(1U << 8);
  //   for (volatile int i = 0; i < 1200; i++);

  //   // Drive both pins HIGH
  //   GPIOA->ODR |=  (1U << 10);
  //   GPIOB->ODR |=  (1U << 8);
  //   for (volatile int i = 0; i < 1200; i++);
  // }
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
  MX_CAN_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  HAL_CAN_Init(&hcan);
  HAL_CAN_Start(&hcan);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN 3 */
  
  // Check if device is ready
  while (1){
    status = HAL_I2C_IsDeviceReady(&hi2c1, BNO055_ADDR, 10, I2C_TIMEOUT_MS);
    if (status == HAL_OK) break;
  }

  // Set to IMU Mode
  uint8_t imuMode = OPR_MODE_IMU;
  while (1) {
    status = HAL_I2C_Mem_Write(&hi2c1, BNO055_ADDR, OPR_MODE, 1, &imuMode, 1, I2C_TIMEOUT_MS);
    if (status == HAL_OK) break;
  }

  // Main Loop - read values
  while (1) {
    status = HAL_OK; // Reset status before reading data

    // Read IMU data (store as big-endian)
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, ACC_DATA_X_LSB, 1, &AccelData[1], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, ACC_DATA_X_MSB, 1, &AccelData[0], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, ACC_DATA_Y_LSB, 1, &AccelData[3], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, ACC_DATA_Y_MSB, 1, &AccelData[2], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, ACC_DATA_Z_LSB, 1, &AccelData[5], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, ACC_DATA_Z_MSB, 1, &AccelData[4], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_DATA_X_LSB, 1, &GyroData[1], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_DATA_X_MSB, 1, &GyroData[0], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_DATA_Y_LSB, 1, &GyroData[3], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_DATA_Y_MSB, 1, &GyroData[2], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_DATA_Z_LSB, 1, &GyroData[5], 1, I2C_TIMEOUT_MS);
    status |= HAL_I2C_Mem_Read(&hi2c1, BNO055_ADDR, GYR_DATA_Z_MSB, 1, &GyroData[4], 1, I2C_TIMEOUT_MS);
    if (status != HAL_OK) {
      continue;
    }

    // Transmit CAN messages
    uint32_t freeBoxes = HAL_CAN_GetTxMailboxesFreeLevel(&hcan);
    if (freeBoxes == 0) {
      HAL_CAN_AbortTxRequest(&hcan, CAN_TX_MAILBOX0 | CAN_TX_MAILBOX1 | CAN_TX_MAILBOX2); // Abort any pending transmissions to free up mailboxes
      // continue; // No free mailboxes, skip this iteration
    }

    HAL_CAN_AddTxMessage(&hcan, &AccelHeader, AccelData, &Mailbox);
    HAL_CAN_AddTxMessage(&hcan, &GyroHeader, GyroData, &Mailbox);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 1;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_10TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_5TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x0010020A;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */
  
  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin : PA1 */
  GPIO_InitStruct.Pin = GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
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
#ifdef USE_FULL_ASSERT
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
