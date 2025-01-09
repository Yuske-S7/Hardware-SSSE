#include <stdio.h>
#include "utils/buzzer.h"
#include "driver/ledc.h"

void app_main(void) {
    buzzer_init();
    printf("Activation du buzzer...\n");
    buzzer_start(5000);
    printf("Buzzer arrêté.\n");
}