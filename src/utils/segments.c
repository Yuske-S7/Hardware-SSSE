#include "segments.h"

#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void segment_init() {
    // Configurer les GPIOs des segments comme sorties
    gpio_config_t segment_config = {
        .pin_bit_mask =
            (1ULL << SEGMENT_GPIO_TOP) | (1ULL << SEGMENT_GPIO_TOP_LEFT) |
            (1ULL << SEGMENT_GPIO_TOP_RIGHT) | (1ULL << SEGMENT_GPIO_MID) |
            (1ULL << SEGMENT_GPIO_BOT) | (1ULL << SEGMENT_GPIO_BOT_LEFT) |
            (1ULL << SEGMENT_GPIO_BOT_RIGHT) | (1ULL << SEGMENT_GPIO_POINT),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&segment_config);

    // Configurer les GPIOs des latches comme sorties
    gpio_config_t latch_config = {
        .pin_bit_mask = (1ULL << LATCH_ONE) | (1ULL << LATCH_SECOND) |
                        (1ULL << LATCH_THIRD) | (1ULL << LATCH_FOURTH) |
                        (1ULL << LATCH_FIFTH) | (1ULL << LATCH_SIXTH),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&latch_config);

    // Configurer le GPIO de la cathode comme sortie
    gpio_config_t cathode_config = {.pin_bit_mask = (1ULL << CATHODE),
                                    .mode = GPIO_MODE_OUTPUT,
                                    .pull_up_en = GPIO_PULLUP_DISABLE,
                                    .pull_down_en = GPIO_PULLDOWN_DISABLE,
                                    .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&cathode_config);
}

void segment_display_all(int numLatch) {
    printf("segment_display_all: trying to display : %d\n", numLatch);
    gpio_set_level(numLatch, 1);

    gpio_set_level(SEGMENT_GPIO_TOP, 1);
    gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
    gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
    gpio_set_level(SEGMENT_GPIO_MID, 1);
    gpio_set_level(SEGMENT_GPIO_BOT, 1);
    gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
    gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    gpio_set_level(SEGMENT_GPIO_POINT, 1);

    vTaskDelay(5000 / portTICK_PERIOD_MS);

    gpio_set_level(numLatch, 0);
    printf("segment_display_all: Turn of segment : %d\n", numLatch);

    gpio_set_level(SEGMENT_GPIO_TOP, 0);
    gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 0);
    gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 0);
    gpio_set_level(SEGMENT_GPIO_MID, 0);
    gpio_set_level(SEGMENT_GPIO_BOT, 0);
    gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 0);
    gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 0);
    gpio_set_level(SEGMENT_GPIO_POINT, 0);
}
