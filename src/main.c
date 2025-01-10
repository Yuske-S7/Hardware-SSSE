#include <stdio.h>
#include "utils/buzzer.h"
#include "utils/pushButton.h"
#include "driver/ledc.h"
#include "utils/segments.h"

void app_main(void) {
    /*
    buzzer_init();
    printf("Activation du buzzer...\n");
    buzzer_start(1000);
    printf("Buzzer arrêté.\n");

    trigger_timer(50);
   */
    gpio_set_level(GPIO_NUM_0, 1);
    segment_init();
    printf("Segments initialised\n");

    segment_display_all(LATCH_SECOND);

    vTaskDelay(5000 / portTICK_PERIOD_MS);
}