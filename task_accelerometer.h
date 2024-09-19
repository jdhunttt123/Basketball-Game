/*
 * accelerometer.h
 *
 *  Created on: Dec 12, 2022
 *      Author: dagrawal23, jdhunt
 */


/* RTOS header files */

#ifndef TASK_ACCELEROMETER_H_
#define TASK_ACCELEROMETER_H_

#include "main.h"

extern TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;
extern TaskHandle_t Task_Accelerometer_Timer_Handle;
extern QueueHandle_t Direction_Data;

typedef enum {
    DIR_CENTER,
    DIR_LEFT,
    DIR_RIGHT,

} ACCELEROMETER_DIR_t;

void accelerometer_init();
void Task_Accelerometer_Timer(void *pvParameters);
void Task_Accelerometer_Bottom_Half(void *pvParameters);
void ADC14_IRQHandler(void);





#endif /* TASK_ACCELEROMETER_H_ */
