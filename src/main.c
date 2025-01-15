#include <driver/ledc.h>
#include <stdio.h>

#include "test_mode/test_mode.h"

void app_main(void) {
    // Buzzer
    buzzer_init();
    printf("Activation du buzzer...\n");
    for (int i = 0; i < 4; i++) {
        buzzer_start(1000);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    printf("Buzzer arrêté.\n");

    /* TODO : add condition => test mode or normal mode */

    // Test mode
    test_display();
}
