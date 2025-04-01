/************************************************
* @file    main.c 
* @author  APBashara
* @date    9/2024
* 
* @brief   Main Code to run IMU Board
***********************************************/

#include "stm32f042x6.h"
#include "main.h"

/* Function Calls -----------------------------------------------------------*/
void main() {
    // Initialize the system clock to 48MHz
    Sysclock_48();

    // Initialize CAN1
    CAN_Init();

    // Start CAN communication
    CAN_Start();

    while (1) {
        // Main loop
    }
}