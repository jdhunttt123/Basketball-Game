/*
 * accelerometer.c
 *
 *  Created on: Dec 12, 2022
 *      Author: dagrawal23, jdhunt
 */

#include <task_accelerometer.h>

QueueHandle_t Direction_Data; // Queue used to draw directional data
TaskHandle_t Task_Accelerometer_Bottom_Half_Handle;
TaskHandle_t Task_Accelerometer_Timer_Handle;

volatile uint32_t X_DIR = 0;
volatile uint32_t Y_DIR = 0;
ACCELEROMETER_DIR_t dir; // Direction to be added to data queue
void accelerometer_init()
{
//initialize pins for x, y, z directions on accelerometer
    P6->SEL0 |= (BIT1 | BIT0 );
    P6->SEL1 |= (BIT1 | BIT0 );
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;

    // Configure CTL0 to sample 16-times in pulsed sample mode.
    ADC14->CTL0 = ADC14_CTL0_SHP | ADC14_CTL0_SHT02;
    // NEW -- Indicate that this is a sequence-of-channels.
    ADC14->CTL0 |= ADC14_CTL0_CONSEQ_1;
    // Configure ADC to return 12-bit values
    ADC14->CTL1 = ADC14_CTL1_RES_2;
    // Associate the X direction analog signal with MEM[0]
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_14;
    // Associate the Y direction analog signal with MEM[1]
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_13;

    // this is the end of a sequence.

    ADC14->MCTL[1] |= BIT7;

    // Enable interrupts in the ADC AFTER a value is written into MEM[1].
    ADC14->IER0 = ADC14_IER0_IE1;

    // Enable ADC Interrupt in the NVIC
    NVIC_EnableIRQ(ADC14_IRQn);
    NVIC_SetPriority(ADC14_IRQn, 1);
    // Turn ADC ON
    ADC14->CTL0 |= ADC14_CTL0_ON;

}

/******************************************************************************
 * Used to start an ADC14 Conversion every 100 ms
 ******************************************************************************/
void Task_Accelerometer_Timer(void *pvParameters)
{
    while (1)
    {
        /*
         * Start the ADC conversion
         */
        ADC14->CTL0 |= ADC14_CTL0_SC | ADC14_CTL0_ENC;

        /*
         * Delay 100mS
         */
        vTaskDelay(pdMS_TO_TICKS(100));

    }
}

/******************************************************************************
 * Bottom Half Task.  Examines the ADC data from the accelerometer on the MKII
 * and assigns direction of movement.
 ******************************************************************************/
void Task_Accelerometer_Bottom_Half(void *pvParameters)
{
    dir = DIR_CENTER;

    while (1)
    {
        /*
         * Wait until we get a task notification from the ADC14 ISR
         */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /*
         * Set the dir variable to one of the following values based
         * on the values of X_DIR
         *
         */

        int xoffset = X_DIR - 2050;


        if (abs(xoffset) <= 140)
        {
            dir = DIR_CENTER;

        }
        else
        {
            if (xoffset < 0)
                dir = DIR_LEFT;
            else
                dir = DIR_RIGHT;

        }

//send new direction to queue

        xQueueSend(Direction_Data, &dir, portMAX_DELAY);


    }
}

/******************************************************************************
 * Top Half of ADC14 Handler.
 ******************************************************************************/
void ADC14_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    X_DIR = ADC14->MEM[0]; // Read the value and clear the interrupt
    Y_DIR = ADC14->MEM[1]; // Read the value and clear the interrupt

   //notify bottom half task
    vTaskNotifyGiveFromISR(Task_Accelerometer_Bottom_Half_Handle,
                           &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}

