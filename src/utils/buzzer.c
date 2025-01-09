#include "buzzer.h"

int trigger_buzzer(int seconds) {
    if (gpio_set_level(BUZZER_GPIO_PIN, 1) == ESP_ERR_INVALID_ARG)
        return 0;
    vTaskDelay(seconds * 1000 / portTICK_PERIOD_MS);
    if (gpio_set_level(BUZZER_GPIO_PIN, 0) == ESP_ERR_INVALID_ARG)
        return 0;

    return 1;
}