/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define I2C_TIMEOUT_MS                        (100) // Timeout for I2C in ms
#define BNO055_ADDR                           (0x28 << 1) // I2C address of the BNO055 IMU, left shifted for HAL functions

#define ACCEL_MESSAGE_ID                      (0x100)
#define GYRO_MESSAGE_ID                       (0x101)

#define ACC_DATA_X_LSB                        (0x08)
#define ACC_DATA_X_MSB                        (0x09)
#define ACC_DATA_Y_LSB                        (0x0A)
#define ACC_DATA_Y_MSB                        (0x0B)
#define ACC_DATA_Z_LSB                        (0x0C)
#define ACC_DATA_Z_MSB                        (0x0D)

#define GYR_DATA_X_LSB                        (0x14)
#define GYR_DATA_X_MSB                        (0x15)
#define GYR_DATA_Y_LSB                        (0x16)
#define GYR_DATA_Y_MSB                        (0x17)
#define GYR_DATA_Z_LSB                        (0x18)
#define GYR_DATA_Z_MSB                        (0x19)

#define LIA_DATA_X_LSB                        (0x28)
#define LIA_DATA_X_MSB                        (0x29)
#define LIA_DATA_Y_LSB                        (0x2A)
#define LIA_DATA_Y_MSB                        (0x2B)
#define LIA_DATA_Z_LSB                        (0x2C)
#define LIA_DATA_Z_MSB                        (0x2D)

#define CALIB_STAT                            (0x35)
#define OPR_MODE                              (0x3D)

#define OPR_MODE_IMU                          (0b00001000)
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
