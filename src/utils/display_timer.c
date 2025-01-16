#include "display_timer.h"

void save_dtime(struct dtime *dt) {
    if (is_button_pressed(HOURS_PUSHBUTTON_GPIO_PIN, pdMS_TO_TICKS(100))) {
        if (is_button_pressed(PLUS_PUSHBUTTON_GPIO_PIN, pdMS_TO_TICKS(100))) {
            dt->hours = (dt->hours + 1) % 24;  // Incrémenter les heures
        } else if (is_button_pressed(MINUS_PUSHBUTTON_GPIO_PIN,
                                     pdMS_TO_TICKS(100))) {
            dt->hours = (dt->hours == 0)
                            ? 23
                            : dt->hours - 1;  // Décrémenter les heures
        }
    }

    if (is_button_pressed(MINUTES_PUSHBUTTON_GPIO_PIN, pdMS_TO_TICKS(100))) {
        if (is_button_pressed(PLUS_PUSHBUTTON_GPIO_PIN, pdMS_TO_TICKS(100))) {
            dt->minutes = (dt->minutes + 1) % 60;  // Incrémenter les minutes
        } else if (is_button_pressed(MINUS_PUSHBUTTON_GPIO_PIN,
                                     pdMS_TO_TICKS(100))) {
            dt->minutes = (dt->minutes == 0)
                              ? 59
                              : dt->minutes - 1;  // Décrémenter les minutes
        }
    }

    if (is_button_pressed(SECONDS_PUSHBUTTON_GPIO_PIN, pdMS_TO_TICKS(100))) {
        if (is_button_pressed(PLUS_PUSHBUTTON_GPIO_PIN, pdMS_TO_TICKS(100))) {
            dt->seconds = (dt->seconds + 1) % 60;  // Incrémenter les secondes
        } else if (is_button_pressed(MINUS_PUSHBUTTON_GPIO_PIN,
                                     pdMS_TO_TICKS(100))) {
            dt->seconds = (dt->seconds == 0)
                              ? 59
                              : dt->seconds - 1;  // Décrémenter les secondes
        }
    }
}

void simultaneous_button_time_setting(void *pvParameters, struct dtime *dt) {
    const gpio_num_t monitored_buttons[] = {PLUS_PUSHBUTTON_GPIO_PIN,
                                            MINUS_PUSHBUTTON_GPIO_PIN};
    const size_t monitored_count =
        sizeof(monitored_buttons) / sizeof(monitored_buttons[0]);

    while (1) {
        if (are_buttons_pressed(monitored_buttons, monitored_count,
                                pdMS_TO_TICKS(300))) {
            printf("Entering time setting mode\n");
            save_dtime(dt);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}