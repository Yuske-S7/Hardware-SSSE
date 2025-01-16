#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <stdio.h>

#define SECONDS_PUSHBUTTON_GPIO_PIN 35
#define MINUTES_PUSHBUTTON_GPIO_PIN 36
#define HOURS_PUSHBUTTON_GPIO_PIN 39

#define PLUS_PUSHBUTTON_GPIO_PIN 4
#define MINUS_PUSHBUTTON_GPIO_PIN 5

static const gpio_num_t button_pins[] = {
    SECONDS_PUSHBUTTON_GPIO_PIN, MINUTES_PUSHBUTTON_GPIO_PIN,
    HOURS_PUSHBUTTON_GPIO_PIN, PLUS_PUSHBUTTON_GPIO_PIN,
    MINUS_PUSHBUTTON_GPIO_PIN};

static void configure_buttons(const gpio_num_t *pins, size_t count);
void trigger_timer(TaskHandle_t xBUZZER_HANDLER);
void simultaneous_button_task_mode_test(void *pvParameters);
static bool are_buttons_pressed(const gpio_num_t *pins, size_t count,
                                TickType_t delay_ticks);
static bool is_button_pressed(gpio_num_t pin, TickType_t delay_ticks);

#endif  // PUSHBUTTON_H
