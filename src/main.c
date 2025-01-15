#include <driver/ledc.h>
#include <stdio.h>

#include "test_mode/test_mode.h"

void app_main(void) {
    // Buzzer
    buzzer_init();
    segment_init();

    xTaskCreate(test_display, "chenillard", 2048, NULL, 5, NULL);
    xTaskCreate(buzzer_on_tension, "buzzer_on_tension", 2048, NULL, 5, NULL);
    /* TODO : add condition => test mode or normal mode */

}
