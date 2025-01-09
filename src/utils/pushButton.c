#include "pushButton.h"

void trigger_timer(int seconds)
{
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SECONDS_PUSHBUTTON_GPIO_PIN) |
                        (1ULL << MINUTES_PUSHBUTTON_GPIO_PIN) |
                        (1ULL << HOURS_PUSHBUTTON_GPIO_PIN),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    while (1)
    {
        if (gpio_set_level(SECONDS_PUSHBUTTON_GPIO_PIN) == 0)
        {
            printf("Seconds push button: (GPIO %d) pressed\n", SECONDS_PUSHBUTTON_GPIO_PIN);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        if (gpio_set_level(MINUTES_PUSHBUTTON_GPIO_PIN) == 0)
        {
            printf("Minutes push button: (GPIO %d) pressed\n", MINUTES_PUSHBUTTON_GPIO_PIN);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
        if (gpio_set_level(HOURS_PUSHBUTTON_GPIO_PIN) == 0)
        {
            printf("Hours push button: (GPIO %d) pressed\n", HOURS_PUSHBUTTON_GPIO_PIN);
            vTaskDelay(200 / portTICK_PERIOD_MS);
        }
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);
}