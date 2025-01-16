#include "normal_mode.h"

void entry_normal_mode(void *parameters)
{
    buzzer_start(5000);
    vTaskDelete(NULL);
}
