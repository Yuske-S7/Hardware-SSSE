#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <driver/gpio.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SECONDS_PUSHBUTTON_GPIO_PIN 35
#define MINUTES_PUSHBUTTON_GPIO_PIN 36
#define HOURS_PUSHBUTTON_GPIO_PIN 39

void trigger_timer(int seconds);

#endif //PUSHBUTTON_H
