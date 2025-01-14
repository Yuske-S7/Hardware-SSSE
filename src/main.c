#include <stdio.h>

#include "driver/ledc.h"
#include "utils/buzzer.h"
#include "utils/pushButton.h"
#include "utils/segments.h"

void app_main(void) {
    /*
    buzzer_init();
    printf("Activation du buzzer...\n");
    buzzer_start(1000);
    printf("Buzzer arrêté.\n");

    trigger_timer(50);
    */
    segment_init();

    while (1) {
        segment_display_all(LATCH_ONE);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Pause de 1 seconde

        segment_display_all(LATCH_SECOND);
        vTaskDelay(1000 / portTICK_PERIOD_MS); // Pause de 1 seconde
    }

}
