#include <driver/ledc.h>
#include <stdio.h>

#include "normal_mode/normal_mode.h"
#include "test_mode/test_mode.h"
#include "utils/display_timer.h"

void app_main(void) {
    /* ========---======== BUZZER ========---======== */
    buzzer_init();
    segment_init();
    printf("Init done");

    /* ========---======== TEST MODE ========---======== */

    TaskHandle_t xBUZZER_HANDLER = NULL;

    xTaskCreate(buzzer_on_tension, "buzzer_on_tension", 2048, NULL, 5,
                &xBUZZER_HANDLER);
    /* TODO : add condition => test mode or normal mode */
    xTaskCreate(trigger_timer, "Trigger Timer", 2048, xBUZZER_HANDLER, 5, NULL);

    /* ========---======== NORMAL MODE ========---======== */
    struct dtime t = {0, 0, 0};
    printf("Initial time:\n");
    time_setting(&t);

    // buzzer_play_imperial_march();
}
