/*
 * light.h
 *
 *  Created on: Dec 12, 2022
 *      Author: dagrawal23, jdhunt
 */

#ifndef TASK_LIGHT_H_
#define TASK_LIGHT_H_


#include "main.h"

extern TaskHandle_t Task_Read_Light_Sensor_Handle;
void Task_Read_Light_Sensor();
void light_sensor_init();

#define  OPT3001_DeviceID    0x44
#define  OPT3001_Data        0x00
#define  OPT3001_CONFIG      0x01
#define  OPT3001_INIT        0x5C10


#endif /* TASK_LIGHT_H_ */
