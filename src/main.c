#include <driver/ledc.h>
#include <stdio.h>

#include "test_mode/test_mode.h"
#include "utils/display_timer.h"

void app_main(void) {
    // Buzzer
    buzzer_init();
    segment_init();
    printf("Init done");
    //
    //    TaskHandle_t xBUZZER_HANDLER = NULL;
    //
    //    // Test mode
    //
    //    xTaskCreate(buzzer_on_tension, "buzzer_on_tension", 2048, NULL, 5,
    //                &xBUZZER_HANDLER);
    //    /* TODO : add condition => test mode or normal mode */
    //    xTaskCreate(trigger_timer, "Trigger Timer", 2048, xBUZZER_HANDLER, 5,
    //    NULL);

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

    // Normal mode
    // buzzer_play_imperial_march();
}
