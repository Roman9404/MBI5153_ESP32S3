#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "esp_log.h"
#include "driver/rmt.h"

#include "display.h"

#define BLINK_GPIO 2

extern uint16_t eye[256];
extern uint16_t green_1[256];
extern uint16_t green_2[256];

extern uint16_t heart_0[256];
extern uint16_t heart_1[256];
extern uint16_t heart_2[256];
extern uint16_t heart_3[256];

int pulse = 100;

void app_main() 
{
    gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    Display_init ();

    rmt_tx_init();
    while (1)
    {
        //*
        mbi_set_frame(eye, green_2, eye);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        mbi_set_frame(eye, green_1, eye);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        /*/
        mbi_set_frame(heart_1, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);
        mbi_set_frame(heart_2, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);
        mbi_set_frame(heart_3, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);
        mbi_set_frame(heart_2, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);

        mbi_set_frame(heart_1, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);
        mbi_set_frame(heart_2, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);
        mbi_set_frame(heart_3, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);
        mbi_set_frame(heart_2, heart_0, heart_0);
        vTaskDelay(pulse / portTICK_PERIOD_MS);
        mbi_set_frame(heart_1, heart_0, heart_0);
        vTaskDelay(250/ portTICK_PERIOD_MS);
        /*/
    }

}