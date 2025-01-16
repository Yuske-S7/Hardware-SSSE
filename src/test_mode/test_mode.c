#include "test_mode.h"

void test_display() {
    for (int i = 0; i < get_latch_gpios_count(); i++) {
        segment_clean_all(get_latch_gpios()[i]);
    }

    for (int i = 0; i < get_latch_gpios_count(); i++) {
        segment_run_light(get_latch_gpios()[i]);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        segment_clean_all(get_latch_gpios()[i]);

        segment_run_light(get_latch_gpios()[i]);
        vTaskDelay(pdMS_TO_TICKS(DELAY_MS));
        segment_clean_all(get_latch_gpios()[i]);
    }

    TaskHandle_t buzzer_task = NULL;
    xTaskCreate(buzzer_waiting, "test_mode_w8_buzzer", 2048, NULL, 5, &buzzer_task);
    xTaskCreate(wait_button_pressed, "test_mode_w8_pressed", 2048, buzzer_task, 5, NULL);
    vTaskDelete(NULL);
}

void wait_button_pressed(void *pvParameters) {
    TaskHandle_t task_to_cut = (TaskHandle_t)pvParameters;
    int stop = 1;

    while (stop) {
        if (gpio_get_level(SECONDS_PUSHBUTTON_GPIO_PIN) == 0 ||
            gpio_get_level(MINUTES_PUSHBUTTON_GPIO_PIN) == 0 ||
            gpio_get_level(HOURS_PUSHBUTTON_GPIO_PIN) == 0 ||
            gpio_get_level(PLUS_PUSHBUTTON_GPIO_PIN) == 0 ||
            gpio_get_level(MINUS_PUSHBUTTON_GPIO_PIN) == 0) {
            stop = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    if (task_to_cut != NULL) {
        vTaskDelete(task_to_cut);
        buzzer_stop();
    }

    TaskHandle_t leave_test = NULL;
    xTaskCreate(test_touch, "test_touch", 2048, NULL, 5, &leave_test);
    xTaskCreate(simultaneous_button_task_mode_test, "sim_button_test", 2048, leave_test, 5, NULL);
    vTaskDelete(NULL);
}

void test_touch()
{
    while (true) {
        if (gpio_get_level(SECONDS_PUSHBUTTON_GPIO_PIN) == 0)
        {
            buzzer_start(200);
            segment_display_char(LATCH_ONE, 'S');
            segment_display_char(LATCH_SECOND, 'S');
            buzzer_stop();
        }
        if (gpio_get_level(MINUTES_PUSHBUTTON_GPIO_PIN) == 0)
        {
            buzzer_start(200);
            segment_display_char(LATCH_FOURTH, 'M');
            segment_display_char(LATCH_THIRD, 'M');
            buzzer_stop();
        }
        if (gpio_get_level(HOURS_PUSHBUTTON_GPIO_PIN) == 0)
        {
            buzzer_start(200);
            segment_display_char(LATCH_SIXTH, 'H');
            segment_display_char(LATCH_FIFTH, 'H');
            buzzer_stop();
        }
        if (gpio_get_level(PLUS_PUSHBUTTON_GPIO_PIN) == 0)
        {
            buzzer_start(200);
            segment_display_char(LATCH_ONE, 'P');
            segment_display_char(LATCH_SECOND, 'P');
            segment_display_char(LATCH_THIRD, 'P');
            segment_display_char(LATCH_FOURTH, 'P');
            segment_display_char(LATCH_FIFTH, 'P');
            segment_display_char(LATCH_SIXTH, 'P');
            buzzer_stop();
        }
        if (gpio_get_level(MINUS_PUSHBUTTON_GPIO_PIN) == 0)
        {
            buzzer_start(200);
            segment_display_char(LATCH_ONE, '-');
            segment_display_char(LATCH_SECOND, '-');
            segment_display_char(LATCH_THIRD, '-');
            segment_display_char(LATCH_FOURTH, '-');
            segment_display_char(LATCH_FIFTH, '-');
            segment_display_char(LATCH_SIXTH, '-');
            buzzer_stop();
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}