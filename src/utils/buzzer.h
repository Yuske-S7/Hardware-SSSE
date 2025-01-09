#ifndef BUZZER_H 
#define BUZZER_H  

#include <driver/gpio.h>
#include <driver/adc.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUZZER_GPIO_PIN 2 // 24

int trigger_buzzer(int seconds);

#endif //BUZZER_H