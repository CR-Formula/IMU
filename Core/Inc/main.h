/************************************************
* @file    main.h 
* @author  APBashara
* @date    3/2025
* 
* @brief   Main Header file for IMU Board
***********************************************/

#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_hal.h"
#include "can.h"
#include "sysclk.h"
#include "gpio.h"

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
