#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "esp_log.h"
#include "driver/rmt.h"

#include "display.h"

#define BLINK_GPIO 2
#define INPUT_GPIO 7
#define ESP_INTR_FLAG_DEFAULT 0

extern uint16_t eye[256];
extern uint16_t green_1[256];
extern uint16_t green_2[256];

extern uint16_t heart_0[256];
extern uint16_t heart_1[256];
extern uint16_t heart_2[256];
extern uint16_t heart_3[256];

int pulse = 100;

int btn = 0;

static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    gpio_intr_disable(INPUT_GPIO);
    btn = !btn;
   // gpio_intr_enable(INPUT_GPIO);
}

void app_main() 
{
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_pad_select_gpio(INPUT_GPIO);
    
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_direction(INPUT_GPIO, GPIO_MODE_INPUT);

    gpio_set_intr_type(INPUT_GPIO, GPIO_INTR_NEGEDGE);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(INPUT_GPIO, gpio_isr_handler, (void*) INPUT_GPIO);
    
    Display_init ();

    rmt_tx_init();
    while (1)
    {
        while (btn == 0)
        {
            mbi_set_frame(eye, green_2, eye);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            mbi_set_frame(eye, green_1, eye);
            vTaskDelay(50 / portTICK_PERIOD_MS);
            gpio_intr_enable(INPUT_GPIO);
        }

        while (btn == 1)
        {
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
            gpio_intr_enable(INPUT_GPIO);
        }
    }

}