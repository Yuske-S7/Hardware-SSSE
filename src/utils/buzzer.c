#include "buzzer.h"

int buzzer_init() {
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .duty_resolution = LEDC_TIMER_13_BIT,
        .freq_hz = BUZZER_PWM_FREQ,
        .clk_cfg = LEDC_AUTO_CLK
    };
    if (ledc_timer_config(&ledc_timer) != ESP_OK)
        return -1;
    ledc_channel_config_t ledc_channel = {
        .gpio_num = GPIO_NUM_2,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0,
        .hpoint = 0
    };
    if (ledc_channel_config(&ledc_channel) != ESP_OK)
        return -1;
    return 0;
}

int buzzer_start(int duration_ms) {
    if (ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 4096) != ESP_OK) // Duty cycle 50%
        return -1;
    if (ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0) != ESP_OK)
        return -1;
    vTaskDelay(duration_ms / portTICK_PERIOD_MS);
    return buzzer_stop();
}

int buzzer_stop() {
    if (ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0) != ESP_OK)    
        return -1;
    if (ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0) != ESP_OK)
        return -1;
    return 0;
}
