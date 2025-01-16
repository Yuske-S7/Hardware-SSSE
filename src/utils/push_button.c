#include "push_button.h"

#include "../test_mode/test_mode.h"

void configure_buttons(const gpio_num_t *pins, size_t count) {
    uint64_t pin_bit_mask = 0;
    for (size_t i = 0; i < count; ++i) {
        pin_bit_mask |= (1ULL << pins[i]);
    }

    gpio_config_t io_conf = {.pin_bit_mask = pin_bit_mask,
                             .mode = GPIO_MODE_INPUT,
                             .pull_up_en = GPIO_PULLUP_ENABLE,
                             .pull_down_en = GPIO_PULLDOWN_DISABLE,
                             .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);
}

bool are_buttons_pressed(const gpio_num_t *pins, size_t count,
                         TickType_t delay_ticks) {
    TickType_t start_time = xTaskGetTickCount();

    while ((xTaskGetTickCount() - start_time) < delay_ticks) {
        bool all_pressed = true;

        for (size_t i = 0; i < count; ++i) {
            if (gpio_get_level(pins[i]) != 0) {
                all_pressed = false;
                break;
            }
        }

        if (!all_pressed) {
            return false;
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }

    return true;
}

void simultaneous_button_task(TaskHandle_t task_to_cut) {
    const gpio_num_t monitored_buttons[] = {HOURS_PUSHBUTTON_GPIO_PIN,
                                            MINUTES_PUSHBUTTON_GPIO_PIN,
                                            SECONDS_PUSHBUTTON_GPIO_PIN};
    size_t monitored_count =
        sizeof(monitored_buttons) / sizeof(monitored_buttons[0]);

    int cpt = 0;

    while (1) {
        if (are_buttons_pressed(monitored_buttons, monitored_count,
                                100 / portTICK_PERIOD_MS)) {
            printf(
                "Hours, Minutes, and Seconds buttons pressed simultaneously "
                "for %d ms\n",
                100);
            if (task_to_cut != NULL) {
                vTaskDelete(task_to_cut);
                task_to_cut = NULL;
                buzzer_stop();
                xTaskCreate(test_display, "chenillard", 2048, NULL, 5, NULL);
            }
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);
        cpt++;
        if (cpt == 120) {
            printf("calling normal mode");
            xTaskCreate(entry_normal_mode, "noraml mode from normal", 2048,
                        NULL, 5, NULL);
            vTaskDelete(NULL);
        }
    }
}

void simultaneous_button_task_mode_test(void *pvParameters) {
    TaskHandle_t task_to_cut = (TaskHandle_t)pvParameters;
    const gpio_num_t monitored_buttons[] = {PLUS_PUSHBUTTON_GPIO_PIN,
                                            MINUS_PUSHBUTTON_GPIO_PIN};
    size_t monitored_count =
        sizeof(monitored_buttons) / sizeof(monitored_buttons[0]);

    while (1) {
        if (are_buttons_pressed(monitored_buttons, monitored_count,
                                100 / portTICK_PERIOD_MS)) {
            printf(
                "Hours, Minutes, and Seconds buttons pressed simultaneously "
                "for %d ms\n",
                100);
            if (task_to_cut != NULL) {
                vTaskDelete(task_to_cut);
                task_to_cut = NULL;
                buzzer_stop();
                segment_clean_all(LATCH_ONE);
                segment_clean_all(LATCH_SECOND);
                segment_clean_all(LATCH_THIRD);
                segment_clean_all(LATCH_FOURTH);
                segment_clean_all(LATCH_FIFTH);
                segment_clean_all(LATCH_SIXTH);
                buzzer_start(1000);
                vTaskDelay(50 / portTICK_PERIOD_MS);
                buzzer_stop();
                vTaskDelay(50 / portTICK_PERIOD_MS);
                buzzer_start(1000);
                vTaskDelay(50 / portTICK_PERIOD_MS);
                buzzer_stop();
                segment_display_char(LATCH_ONE, '.');
                segment_display_char(LATCH_SECOND, '.');
                segment_display_char(LATCH_THIRD, '.');
                segment_display_char(LATCH_FOURTH, '.');
                segment_display_char(LATCH_FIFTH, '.');
                segment_display_char(LATCH_SIXTH, '.');
                xTaskCreate(entry_normal_mode, "noraml mode from test", 2048,
                            NULL, 5, NULL);
                printf("lancer le mode normal");
            }
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void trigger_timer(void *pvParameters) {
    TaskHandle_t xBUZZER_HANDLER = (TaskHandle_t)pvParameters;
    configure_buttons(button_pins,
                      sizeof(button_pins) / sizeof(button_pins[0]));
    simultaneous_button_task(xBUZZER_HANDLER);
}
