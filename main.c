/*
 * main.c
 *
 * Student1: Devansh Agrawal
 * Student2: James Hunt
 *
 */

/*
 * Copyright (c) 2016-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ======== main_freertos.c ========
 */
#include "main.h"

/*
 *  ======== main ========
 */
int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    init(); //initialize board

    /* Create Sound Semaphores */
    Sem_Score = xSemaphoreCreateBinary();
    Sem_Win = xSemaphoreCreateBinary();

    /* Create Data Queues */
    LightData = xQueueCreate(10, sizeof(uint16_t));
    Direction_Data = xQueueCreate(10, sizeof(uint32_t));

    /* Assign Tasks to scheduler */

    //Task to calculate direction
    xTaskCreate(Task_Accelerometer_Bottom_Half, "Task_Accelerometer",
    configMINIMAL_STACK_SIZE,
                NULL, 4, &Task_Accelerometer_Bottom_Half_Handle);
    //task to start conversion from accelerometer data
    xTaskCreate(Task_Accelerometer_Timer, "Task_Accelerometer_Timer",
    configMINIMAL_STACK_SIZE,
                NULL, 3, &Task_Accelerometer_Timer_Handle);
    //task to read light sensor data
    xTaskCreate(Task_Read_Light_Sensor, "Task_Read_Light_Sensor",
    configMINIMAL_STACK_SIZE,
                NULL, 2, &Task_Read_Light_Sensor_Handle);
    //main game task, draws lcd
    xTaskCreate(task_draw_images, "Task_Draw_Images",
    configMINIMAL_STACK_SIZE,
                NULL, 3, &Task_Draw_Images);
    //task to play sound when score is incremented
    xTaskCreate(task_scoresound, "Task_ScoreSound",
    configMINIMAL_STACK_SIZE,
                NULL, 1, &scoreSoundTaskHandle);
    //task to play sound when user wins game
    xTaskCreate(task_winsound, "Task_WinSound",
    configMINIMAL_STACK_SIZE,
                NULL, 1, &winSoundTaskHandle);

    //Give semaphores to draw task
    xSemaphoreGive(Sem_Score);
    xSemaphoreGive(Sem_Win);

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    while (1)
    {
    };
    return (0);
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while (1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    //Handle FreeRTOS Stack Overflow
    while (1)
    {
    }
}

/*
 * Initialize all board peripherals
 *
 */
void init()
{
    ece353_MKII_RGB_IO_Init(false);
    ece353_rgb_init();
    ece353_rgb(false, false, false);
    ece353_MKII_RGB_LED(false, false, false);
    ece353_init_led1();
    ece353_led1(false);
    lcd_init();
    accelerometer_init();
    i2c_init();
    light_sensor_init();
    buzzerInit();
    __enable_irq();
}
