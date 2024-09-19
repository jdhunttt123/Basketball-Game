/*
 * light.c
 *
 *  Created on: Dec 12, 2022
 *      Author: dagrawal23, jdhunt
 */

#include <task_light.h>

TaskHandle_t Task_Read_Light_Sensor_Handle;

/*
 * Initialize opt3001 light sensor
 */
void light_sensor_init()
{
    i2c_write_16(OPT3001_DeviceID, OPT3001_CONFIG, OPT3001_INIT);

}

/*
 * Read data from opt3001 light sensor and convert to lux
 */
void Task_Read_Light_Sensor(void *pvParameters)
{
    while (1)
    {
        uint16_t data;
        data = i2c_read_16(OPT3001_DeviceID, OPT3001_Data);

        //convert into lux
        uint16_t exponent = (0xF000 & data) >> 12;
        uint16_t fractionalResult = (data & 0x0FFF);
        uint16_t lux = 0.01 * pow(2, exponent) * fractionalResult;
        xQueueSend(LightData, &lux, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(50));

    }
}

