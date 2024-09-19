/*
 * buzzer.h
 *
 *  Created on: Dec 14, 2022
 *      Author: dagrawal23, jdhunt
 */

#ifndef TASK_BUZZER_H_
#define TASK_BUZZER_H_

#include "main.h"

extern SemaphoreHandle_t Sem_Score;
extern SemaphoreHandle_t Sem_Win;
extern TaskHandle_t scoreSoundTaskHandle;
extern TaskHandle_t winSoundTaskHandle;

void buzzerInit();
void task_scoresound(void *pvParameters);
void task_winsound(void *pvParameters);


#endif /* TASK_BUZZER_H_ */
