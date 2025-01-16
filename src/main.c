#include <driver/ledc.h>
#include <stdio.h>

#include "test_mode/test_mode.h"

void app_main(void) {
    // Buzzer
    buzzer_init();
    segment_init();
    printf("Init done");

    TaskHandle_t xBUZZER_HANDLER = NULL;

    xTaskCreate(buzzer_on_tension, "buzzer_on_tension", 2048, NULL, 5, &xBUZZER_HANDLER);
    /* TODO : add condition => test mode or normal mode */
    xTaskCreate(trigger_timer, "button_on_tension", 2048, xBUZZER_HANDLER, 5, NULL);


}
