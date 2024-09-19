/*
 * buzzer.c
 *
 *  Created on: Dec 14, 2022
 *      Author: dagrawal23, jdhunt
 */
#include <task_buzzer.h>
SemaphoreHandle_t Sem_Score; // Semaphore for Sound task on making basket
SemaphoreHandle_t Sem_Win; // Semaphore for Sound task on winning game
TaskHandle_t scoreSoundTaskHandle;
TaskHandle_t winSoundTaskHandle;

/******************************************************************************
 * Initialize buzzer
 ******************************************************************************/
void buzzerInit()
{
    P2->DIR |= BIT7;
}

/******************************************************************************
 * Upon the user making a basket, activate buzzer to play a tone
 ******************************************************************************/
void task_scoresound(void *pvParameters)
{
    while (1)
    {
        //Take semaphore from current task
        xSemaphoreTake(Sem_Score, portMAX_DELAY);

        //Play score sound with buzzer
        int i;
        for (i = 0; i < 100; i++)
        {
            P2->OUT |= BIT7;
            vTaskDelay(pdMS_TO_TICKS(5));
            P2->OUT &= ~BIT7;
            vTaskDelay(pdMS_TO_TICKS(5));

        }
        P2->OUT &= ~BIT7;

        //Return semaphore and resume previous task
        xSemaphoreGive(Sem_Score);
    }

}

/******************************************************************************
 * Upon the user winning the game, activate buzzer to play a tone
 ******************************************************************************/
void task_winsound(void *pvParameters)
{

    while (1)
    {
        //Take semaphore from current task
        xSemaphoreTake(Sem_Win, portMAX_DELAY);

        //Play winning sound with buzzer
        int i;
        for (i = 0; i < 50; i++)
        {
            P2->OUT |= BIT7;
            vTaskDelay(pdMS_TO_TICKS(15));
            P2->OUT &= ~BIT7;
            vTaskDelay(pdMS_TO_TICKS(3));

        }
        P2->OUT &= ~BIT7;

        //Return semaphore and resume previous task
        xSemaphoreGive(Sem_Win);

    }

}

