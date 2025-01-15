#include "test_mode.h"

void wait_button_pressed(TaskHandle_t task_to_cut);

void test_display() {

    for (int i = 0; i < get_latch_gpios_count(); i++) {
        segment_clean_all(get_latch_gpios()[i]);
    }

    for (int i = 0; i < get_latch_gpios_count(); i++) {
        segment_run_light(get_latch_gpios()[i]);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
        segment_clean_all(get_latch_gpios()[i]);

        segment_run_light(get_latch_gpios()[i]);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
        segment_clean_all(get_latch_gpios()[i]);
    }
    TaskHandle_t buzzer_task = NULL;
    xTaskCreate(buzzer_waiting, "test_mode_w8_buzzer", 2048, NULL, 5, &buzzer_task);
    xTaskCreate(wait_button_pressed, "test_mode_w8_pressed", 2048, buzzer_task, 5, NULL);
    vTaskDelete(NULL);
}

void wait_button_pressed(TaskHandle_t task_to_cut) {

    int stop = 1;
    while (stop)
    {
        if (gpio_get_level(SECONDS_PUSHBUTTON_GPIO_PIN) == 0)
            stop = 0;
        if (gpio_get_level(MINUTES_PUSHBUTTON_GPIO_PIN) == 0)
            stop = 0;
        if (gpio_get_level(HOURS_PUSHBUTTON_GPIO_PIN) == 0)
            stop = 0;
        if (gpio_get_level(PLUS_PUSHBUTTON_GPIO_PIN) == 0)
            stop = 0;
        if (gpio_get_level(MINUS_PUSHBUTTON_GPIO_PIN) == 0)
            stop = 0;
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    if (task_to_cut)
    {
        vTaskDelete(task_to_cut);
        task_to_cut = NULL;
        buzzer_stop();
    }
    vTaskDelete(NULL);
    
}