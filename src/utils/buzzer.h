#ifndef BUZZER_H
#define BUZZER_H

#include <driver/gpio.h>
#include <driver/ledc.h>
#include <esp_adc/adc_oneshot.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define BUZZER_GPIO_PIN 2  // 24
#define BUZZER_PWM_FREQ 2000

void buzzer_start(int duration_ms);
int buzzer_stop(void);
int buzzer_init();
void buzzer_on_tension();

#endif  // BUZZER_H