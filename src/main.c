#include <driver/ledc.h>
#include <stdio.h>

#include "utils/buzzer.h"
#include "utils/push_button.h"
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

    for (int i = 0; i < get_latch_gpios_count(); i++) {
        segment_clean_all(get_latch_gpios()[i]);
    }

    segment_run_light(get_latch_gpios()[1]);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    segment_display_digit(get_latch_gpios()[0], 5);
    segment_display_digit(get_latch_gpios()[1], 6);
    segment_display_digit(get_latch_gpios()[2], 7);
    segment_display_digit(get_latch_gpios()[3], 8);
    segment_display_digit(get_latch_gpios()[4], 8);
    segment_display_digit(get_latch_gpios()[5], 9);
}
