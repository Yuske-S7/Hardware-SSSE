#include "pushButton.h"

void trigger_timer(int seconds)
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
    vTaskDelay(50 / portTICK_PERIOD_MS);
}