#ifndef SEGMENT_H
#define SEGMENT_H

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define SEGMENT_GPIO_TOP 16
#define SEGMENT_GPIO_TOP_LEFT 22
#define SEGMENT_GPIO_TOP_RIGHT 17
#define SEGMENT_GPIO_MID 23
#define SEGMENT_GPIO_BOT 19
#define SEGMENT_GPIO_BOT_LEFT 21
#define SEGMENT_GPIO_BOT_RIGHT 18
#define SEGMENT_GPIO_POINT 27

#define LATCH_ONE 32
#define LATCH_SECOND 33
#define LATCH_THIRD 12
#define LATCH_FOURTH 13
#define LATCH_FIFTH 14
#define LATCH_SIXTH 15

#define OUTPUT_ENABLE 0
#define CATHODE 25

#define SHORT_DELAY_MS 1
#define LONG_DELAY_MS 500

void segment_init();
void segment_display(int latch_gpio, int state);
void segment_display_all(int latch_gpio);
void segment_clean_all(int latch_gpio);
const int* get_latch_gpios();
int get_latch_gpios_count();
void segment_display_digit(int latch_gpio, int digit);
void segment_display_char(int latch_gpio, char character);
void segment_run_light(int latch_gpio);

#endif  // SEGMENT_H