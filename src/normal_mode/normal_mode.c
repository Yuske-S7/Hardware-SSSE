#include "normal_mode.h"

void entry_normal_mode(void *parameters) {
    buzzer_start(5000);
    vTaskDelete(NULL);
}

void time_setting() {
    struct dtime t = {1, 1, 1};
    while (1) {
        save_dtime_hours(&t, true);
        vTaskDelay(pdMS_TO_TICKS(1000));
        save_dtime_minutes(&t, true);
        vTaskDelay(pdMS_TO_TICKS(1000));
        save_dtime_seconds(&t, true);
        vTaskDelay(pdMS_TO_TICKS(1000));

        printf("%02d:%02d:%02d\n", t.hours, t.minutes, t.seconds);
    }
}
