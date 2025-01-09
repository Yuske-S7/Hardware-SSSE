#pragma once

#include <stdio.h>
#include "utils/buzzer.h"
#include "utils/pushButton.h"
#include "driver/ledc.h"

void app_main(void) {
    buzzer_init();
    printf("Activation du buzzer...\n");
    buzzer_start(5000);
    printf("Buzzer arrêté.\n");

    trigger_timer(50);
}