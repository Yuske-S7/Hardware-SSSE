#ifndef BUZZER_H 
#define BUZZER_H  

#include <driver/gpio.h>
#include <driver/adc.h> 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <driver/ledc.h>

#define BUZZER_GPIO_PIN 2 // 24
#define BUZZER_PWM_FREQ 2000


int buzzer_start(int duration_ms);
int buzzer_stop(void);
int buzzer_init();

#endif //BUZZER_H