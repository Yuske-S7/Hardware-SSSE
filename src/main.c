#include <driver/ledc.h>
#include <stdio.h>

#include "utils/buzzer.h"
#include "utils/pushButton.h"
#include "utils/segments.h"
#include "utils/state.h"

void app_main(void) {
    // Buzzer
    buzzer_init();
    printf("Activation du buzzer...\n");
    buzzer_start(1000);
    printf("Buzzer arrêté.\n");

    // Push button
    trigger_timer();

    // 7 segments display
    segment_init();
    segment_clean_all(LATCH_ONE);
    segment_clean_all(LATCH_SECOND);
    segment_clean_all(LATCH_THIRD);
    segment_clean_all(LATCH_FOURTH);
    segment_clean_all(LATCH_FIFTH);
    segment_clean_all(LATCH_SIXTH);

    while (1) {
        segment_display_all(LATCH_ONE);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        segment_display_all(LATCH_SECOND);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        segment_display_all(LATCH_THIRD);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        segment_display_all(LATCH_FOURTH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        segment_display_all(LATCH_FIFTH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        segment_display_all(LATCH_SIXTH);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
