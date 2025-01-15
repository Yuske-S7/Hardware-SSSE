#include "buzzer.h"

int buzzer_init() {
    ledc_timer_config_t ledc_timer = {.speed_mode = LEDC_LOW_SPEED_MODE,
                                      .timer_num = LEDC_TIMER_0,
                                      .duty_resolution = LEDC_TIMER_13_BIT,
                                      .freq_hz = BUZZER_PWM_FREQ,
                                      .clk_cfg = LEDC_AUTO_CLK};
    if (ledc_timer_config(&ledc_timer) != ESP_OK) return -1;
    ledc_channel_config_t ledc_channel = {.gpio_num = GPIO_NUM_2,
                                          .speed_mode = LEDC_LOW_SPEED_MODE,
                                          .channel = LEDC_CHANNEL_0,
                                          .timer_sel = LEDC_TIMER_0,
                                          .duty = 0,
                                          .hpoint = 0};
    if (ledc_channel_config(&ledc_channel) != ESP_OK) return -1;
    return 0;
}

void buzzer_start(int duration_ms) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 4096);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    vTaskDelay(duration_ms / portTICK_PERIOD_MS);
    buzzer_stop();
}

void buzzer_on_tension() {
    for (int i = 0; i < 4; i++) {
        buzzer_start(1000);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void buzzer_waiting() {
    while (true) {
        buzzer_start(1000);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

int buzzer_stop() {
    if (ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0) != ESP_OK)
        return -1;
    if (ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0) != ESP_OK)
        return -1;
    return 0;
}
