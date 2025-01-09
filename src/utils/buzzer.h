#ifndef BUZZER_H 
#define BUZZER_H  

#include <driver/gpio.h>
#include <driver/adc.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/ledc.h>

#define BUZZER_GPIO_PIN 2 // 24
#define BUZZER_PWM_FREQ 2000

void buzzer_start(int duration_ms);
void buzzer_stop(void);
void buzzer_init();

#endif //BUZZER_H