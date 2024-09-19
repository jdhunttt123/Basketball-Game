/*
 * draw.c
 *
 *  Created on: Dec 13, 2022
 *      Author: dagrawal23, jdhunt
 */
#include <task_draw.h>
QueueHandle_t LightData;
TaskHandle_t Task_Draw_Images;
int score = 0; // int to keep track of score
int misses = 0; //int to keep track of misses

/*
 * draws the score text with the appropriate number
 */
void draw_score()
{
    switch (score)
    {
    case 0:
        lcd_draw_image(120, 65, 9, 5, zeroBitmaps, LCD_COLOR_RED,
                       LCD_COLOR_BLACK);
        break;
    case 1:
        lcd_draw_image(120, 65, 9, 3, oneBitmaps, LCD_COLOR_RED,
                       LCD_COLOR_BLACK);
        break;
    case 2:
        lcd_draw_image(120, 65, 9, 5, twoBitmaps, LCD_COLOR_RED,
                       LCD_COLOR_BLACK);
        break;
    case 3:
        lcd_draw_image(120, 65, 9, 3, threeBitmaps, LCD_COLOR_RED,
                       LCD_COLOR_BLACK);
        break;
    }

    lcd_draw_image(120, 90, scoreWidth, scoreHeight, SBitmaps, LCD_COLOR_WHITE,
                   LCD_COLOR_BLACK);
}

void task_draw_images()
{
    //take sound semaphores and only give them when the sound is to be played
    xSemaphoreTake(Sem_Score, portMAX_DELAY);
    xSemaphoreTake(Sem_Win, portMAX_DELAY);
    int x = 60;
    int y = 10;
    int basketx = 90;
    bool scored = false;

    int yspeed = 1;
    ACCELEROMETER_DIR_t dir;
    uint16_t ballColor = LCD_COLOR_ORANGE;
    uint16_t basketColor = LCD_COLOR_CYAN;
    uint16_t lux = 250;

    while (1)
    {
        //get direction and light sensor data
        xQueueReceive(Direction_Data, &dir, pdMS_TO_TICKS(10));
        xQueueReceive(LightData, &lux, pdMS_TO_TICKS(2));

        //switch to dark mode colors
        if (lux < 30)
        {
            ballColor = LCD_COLOR_CYAN;
            basketColor = LCD_COLOR_ORANGE;
        }
        //switch to light mode colors
        else
        {
            ballColor = LCD_COLOR_ORANGE;
            basketColor = LCD_COLOR_CYAN;
        }

        //change x position and ensure image in bounds
        if (dir == DIR_RIGHT)
        {

            if (x + 2 < 102)
                x = x + 2;
            else
                x = 102;
        }
        else if (dir == DIR_LEFT)
        {
            if (x - 2 > 20)
                x = x - 2;
            else
                x = 20;
        }

        //change y position and ensure image in bounds
        if (y + yspeed < 100)
        {
            y = y + yspeed;

        }
        else
        {
            y = 100;
        }

        //if ball falls into basket then scored is true
        if (abs(basketx - x) < 5 && abs(110 - y) < 15)
            scored = true;
        //draw ball
        lcd_draw_image(x, y, basketballWidthPixels, basketballHeightPixels,
                       BasketballBitmap, ballColor, LCD_COLOR_BLACK);
        //draw score
        draw_score();
        //draw basket
        lcd_draw_image(basketx, 110, basketWidthPixels, basketHeightPixels,
                       basketBitmaps, basketColor, LCD_COLOR_BLACK);

        if (y == 100)
        {
            //erase ball and basket
            lcd_draw_rectangle(x, y, basketballWidthPixels,
                               basketballHeightPixels, LCD_COLOR_BLACK);
            lcd_draw_rectangle(basketx, 110, basketWidthPixels,
                               basketHeightPixels, LCD_COLOR_BLACK);
            //if scored, increase score and ball falling speed
            if (scored == true)
            {
                scored = false;
                score++;
                yspeed++;
                //erase old score number and redraw score
                lcd_draw_rectangle(120, 65, 9, 5, LCD_COLOR_BLACK);
                draw_score();

                //play  sound and draw nice shot if they scored and score < 3
                if (score < 3)
                {
                    lcd_draw_image(60, 70, niceshotWidth, niceshotHeight,
                                   niceshotBitmaps, LCD_COLOR_GREEN,
                                   LCD_COLOR_BLACK);
                    xSemaphoreGive(Sem_Score);

                    vTaskDelay(pdMS_TO_TICKS(50));
                    xSemaphoreTake(Sem_Score, portMAX_DELAY);
                    lcd_draw_rectangle(60, 70, niceshotWidth, niceshotHeight,
                                       LCD_COLOR_BLACK);
                }
            }
            else
            {
                misses++;
                switch (misses)
                {
                case 1:
                    ece353_rgb(true, false, false); //turn on 1 led for 1 miss and so on..
                    break;
                case 2:
                    ece353_MKII_RGB_LED(true, false, false);
                    break;
                case 3:
                    ece353_led1(true);
                    break;
                }
            }
            draw_score();
            if (score == 3)
            {
                //erase screen
                lcd_draw_rectangle(60, 70, niceshotWidth, niceshotHeight,
                                   LCD_COLOR_BLACK);
                //draw you win
                lcd_draw_image(60, 70, winWidthPixels, winHeightPixels,
                               winBitmaps, LCD_COLOR_CYAN, LCD_COLOR_BLACK);
                //play win sound
                xSemaphoreGive(Sem_Win);
                vTaskDelay(pdMS_TO_TICKS(50));
                xSemaphoreTake(Sem_Win, portMAX_DELAY);
                break;
            }
            if (misses == 3)
            {
                //draw game over
                lcd_draw_image(60, 70, gameoverWidthPixels,
                               gameoverHeightPixels, gameOverbitmaps,
                               LCD_COLOR_MAGENTA, LCD_COLOR_BLACK);
                break;
            }
            // when ball reaches bottom, make it fall again from a random x, into basket placed at random y
            y = 10;
            basketx = (rand() % 70) + 20;
            x = (rand() % 82) + 20;

        }
    }
}

