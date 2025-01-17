#include "normal_mode.h"

void entry_normal_mode(void *parameters) {
    buzzer_start(5000);
    vTaskDelete(NULL);
}

void time_setting(struct dtime *t) {
    xTaskCreate(simultaneous_button_task_mode_song, "musique vador", 2048, NULL, 5, NULL);
    while (true) {
        clock_increment(t);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        print_time_display(t);
    }
}