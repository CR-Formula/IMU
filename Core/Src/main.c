/************************************************
* @file    main.c 
* @author  APBashara
* @date    9/2024
* 
* @brief   Main Code to run IMU Board
***********************************************/

#include "stm32f042x6.h"
#include "main.h"

/* Global Variables ---------------------------------------------------------*/
GPIO_Instance TogglePin;

/* Function Calls -----------------------------------------------------------*/
void main() {
    // Initialize the system clock to 48MHz
    Sysclock_48();

    TogglePin = (GPIO_Instance) {
        .port = GPIOA,
        .pin = GPIO_PIN_5,
        .mode = GPIO_Mode_Output,
        .pull = GPIO_Pull_NoPull,
        .speed = GPIO_Speed_Low
    };
    
    GPIO_Init(&TogglePin);

    while (1) {
        // Main loop
    }
}