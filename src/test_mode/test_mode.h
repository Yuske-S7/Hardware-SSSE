#ifndef TEST_MODE_H
#define TEST_MODE_H

#include "../utils/buzzer.h"
#include "../utils/push_button.h"
#include "../utils/segments.h"
#include "../normal_mode/normal_mode.h"
#include "../utils/imperial_march"
#define DELAY_MS 200

void test_display();
void test_push_button();
void wait_button_pressed(void *pvParameters);
void test_touch();

#endif  // TEST_MODE_H
