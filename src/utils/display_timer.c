#include "display_timer.h"

#define DISPLAY_TIMER_INTERVAL_MS 300

void save_dtime_hours(struct dtime *dt, bool is_increment) {
    if (is_increment) {
        dt->hours = (dt->hours + 1) % 24;
    } else {
        if (dt->hours == 0) {
            dt->hours = 23;
        } else {
            dt->hours--;
        }
    }
}

void save_dtime_minutes(struct dtime *dt, bool is_increment) {
    if (is_increment) {
        dt->minutes = (dt->minutes + 1) % 60;
    } else {
        if (dt->minutes == 0) {
            dt->minutes = 59;
        } else {
            dt->minutes--;
        }
    }
}

void save_dtime_seconds(struct dtime *dt, bool is_increment) {
    if (is_increment) {
        dt->seconds = (dt->seconds + 1) % 60;
    } else {
        if (dt->seconds == 0) {
            dt->seconds = 59;
        } else {
            dt->seconds--;
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
            save_dtime_hours(dt, true);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}