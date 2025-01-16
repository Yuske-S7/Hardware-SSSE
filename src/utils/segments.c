#include "segments.h"

#include <driver/ledc.h>

static const int segment_gpios[] = {
    SEGMENT_GPIO_TOP,       SEGMENT_GPIO_TOP_LEFT, SEGMENT_GPIO_TOP_RIGHT,
    SEGMENT_GPIO_MID,       SEGMENT_GPIO_BOT,      SEGMENT_GPIO_BOT_LEFT,
    SEGMENT_GPIO_BOT_RIGHT, SEGMENT_GPIO_POINT};

static const int latch_gpios[] = {LATCH_ONE,    LATCH_SECOND, LATCH_THIRD,
                                  LATCH_FOURTH, LATCH_FIFTH,  LATCH_SIXTH};

void segment_init() {
    gpio_config_t io_conf = {.pin_bit_mask = 0,
                             .mode = GPIO_MODE_OUTPUT,
                             .pull_up_en = GPIO_PULLUP_DISABLE,
                             .pull_down_en = GPIO_PULLDOWN_DISABLE,
                             .intr_type = GPIO_INTR_DISABLE};

    for (int i = 0; i < sizeof(segment_gpios) / sizeof(segment_gpios[0]); i++) {
        io_conf.pin_bit_mask |= (1ULL << segment_gpios[i]);
    }

    for (int i = 0; i < sizeof(latch_gpios) / sizeof(latch_gpios[0]); i++) {
        io_conf.pin_bit_mask |= (1ULL << latch_gpios[i]);
    }

    io_conf.pin_bit_mask |= (1ULL << OUTPUT_ENABLE);

    gpio_config(&io_conf);

    gpio_set_level(OUTPUT_ENABLE, 1);
}

void segment_display(int latch_gpio, int state) {
    for (int i = 0; i < sizeof(segment_gpios) / sizeof(segment_gpios[0]); i++) {
        gpio_set_level(segment_gpios[i], state);
    }

    gpio_set_level(latch_gpio, 1);
    vTaskDelay(SHORT_DELAY_MS / portTICK_PERIOD_MS);
    gpio_set_level(latch_gpio, 0);

    gpio_set_level(OUTPUT_ENABLE, state);
}

void segment_display_all(int latch_gpio) {
    segment_display(latch_gpio, 1);
}

void segment_clean_all(int latch_gpio) {
    segment_display(latch_gpio, 0);
}

const int* get_latch_gpios() {
    return latch_gpios;
}

int get_latch_gpios_count() {
    return sizeof(latch_gpios) / sizeof(latch_gpios[0]);
}

void segment_display_digit(int latch_gpio, int digit) {
    segment_clean_all(latch_gpio);

    if (digit == 0) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (digit == 1) {
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    } else if (digit == 2) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (digit == 3) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (digit == 4) {
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    } else if (digit == 5) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (digit == 6) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (digit == 7) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    } else if (digit == 8) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (digit == 9) {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    } else {
        printf("Invalid digit: %d\n", digit);
        return;
    }

    gpio_set_level(latch_gpio, 1);
    vTaskDelay(SHORT_DELAY_MS / portTICK_PERIOD_MS);
    gpio_set_level(latch_gpio, 0);

    gpio_set_level(OUTPUT_ENABLE, 0);
}

void segment_display_char(int latch_gpio, char character) {
    segment_clean_all(latch_gpio);

    if (character == 'H') {
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
    } else if (character == 'M') {
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
    } else if (character == 'N') {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    } else if (character == 'S') {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (character == 'P') {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
    } else if (character == 'R') {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    } else if (character == 'F') {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
    } else if (character == 'E') {
        gpio_set_level(SEGMENT_GPIO_TOP, 1);
        gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_MID, 1);
        gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
        gpio_set_level(SEGMENT_GPIO_BOT, 1);
    } else if (character == '-') {
        gpio_set_level(SEGMENT_GPIO_MID, 1);
    } else if (character == '.') {
        gpio_set_level(SEGMENT_GPIO_POINT, 1);
    } else {
        printf("Invalid character: %c\n", character);
        return;
    }

    gpio_set_level(latch_gpio, 1);
    vTaskDelay(SHORT_DELAY_MS / portTICK_PERIOD_MS);
    gpio_set_level(latch_gpio, 0);

    gpio_set_level(OUTPUT_ENABLE, 0);
}

void segment_run_light(int latch_gpio) {
    const int sequence[] = {SEGMENT_GPIO_TOP,       SEGMENT_GPIO_TOP_RIGHT,
                            SEGMENT_GPIO_BOT_RIGHT, SEGMENT_GPIO_BOT,
                            SEGMENT_GPIO_BOT_LEFT,  SEGMENT_GPIO_TOP_LEFT,
                            SEGMENT_GPIO_MID,       SEGMENT_GPIO_POINT};

    segment_clean_all(latch_gpio);
    gpio_set_level(OUTPUT_ENABLE, 0);

    for (size_t i = 0; i < sizeof(sequence) / sizeof(sequence[0]); ++i) {
        gpio_set_level(sequence[i], 1);
        gpio_set_level(latch_gpio, 1);
        vTaskDelay(SHORT_DELAY_MS / portTICK_PERIOD_MS);
        gpio_set_level(latch_gpio, 0);
        vTaskDelay(LONG_DELAY_MS / portTICK_PERIOD_MS);
    }

    gpio_set_level(OUTPUT_ENABLE, 1);
}