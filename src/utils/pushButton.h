#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <stdio.h>
#include "state.h"

#define SECONDS_PUSHBUTTON_GPIO_PIN 35
#define MINUTES_PUSHBUTTON_GPIO_PIN 36
#define HOURS_PUSHBUTTON_GPIO_PIN 39

#define PLUS_PUSHBUTTON_GPIO_PIN 4
#define MINUS_PUSHBUTTON_GPIO_PIN 5

void trigger_timer();

#endif  // PUSHBUTTON_H
