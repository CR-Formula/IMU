/************************************************
* @file    main.c 
* @author  APBashara
* @date    9/2024
* 
* @brief   Main Code to run IMU Board
***********************************************/

#include "stm32f042x6.h"
#include "main.h"

CAN_Frame Accel_Data = {
    .id = ACCEL_MESSAGE_ID,
    .dlc = 8,
    .rtr = CAN_RTR_Data,
    .data = {0}
};

int main() {
    // Init Peripherals
    Sysclock_48(); // 48MHz Sysclock
    CAN_Init();
    CAN_Filters_Init();
    CAN_Start();

    // Define CAN Messages
    Accel_Data.id = ACCEL_MESSAGE_ID;
    Accel_Data.dlc = 8; // 8 bytes of data
    Accel_Data.rtr = CAN_RTR_Data; // Data Frame

    while (1) {
        // TODO: Perform IMU Read and Load into CAN Messages
        // Load dummy data for testing
        for (size_t i = 0; i < 8; i++) {
            Accel_Data.data[i] = i;
        }
        // Send CAN Message
        CAN_Transmit(&Accel_Data);

        // Temp Delay Function
        for (volatile uint32_t i = 0; i < 100000; i++); // Simple delay loop
    }
}