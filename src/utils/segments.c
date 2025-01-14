#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "segments.h"

// Initialiser les GPIO
void segment_init() {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << SEGMENT_GPIO_TOP) |
                        (1ULL << SEGMENT_GPIO_TOP_LEFT) |
                        (1ULL << SEGMENT_GPIO_TOP_RIGHT) |
                        (1ULL << SEGMENT_GPIO_MID) |
                        (1ULL << SEGMENT_GPIO_BOT) |
                        (1ULL << SEGMENT_GPIO_BOT_LEFT) |
                        (1ULL << SEGMENT_GPIO_BOT_RIGHT) |
                        (1ULL << SEGMENT_GPIO_POINT) |
                        (1ULL << LATCH_ONE) |
                        (1ULL << LATCH_SECOND) |
                        (1ULL << LATCH_THIRD) |
                        (1ULL << LATCH_FOURTH) |
                        (1ULL << LATCH_FIFTH) |
                        (1ULL << LATCH_SIXTH) |
                        (1ULL << OUTPUT_ENABLE),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    // Par défaut, désactivez les segments
    gpio_set_level(OUTPUT_ENABLE, 1); // Désactiver les sorties (si OE est actif LOW)
}

// Activer tous les segments sur un latch donné
void segment_display_all(int latch_gpio) {
    // Allumer tous les segments
    gpio_set_level(SEGMENT_GPIO_TOP, 1);
    gpio_set_level(SEGMENT_GPIO_TOP_LEFT, 1);
    gpio_set_level(SEGMENT_GPIO_TOP_RIGHT, 1);
    gpio_set_level(SEGMENT_GPIO_MID, 1);
    gpio_set_level(SEGMENT_GPIO_BOT, 1);
    gpio_set_level(SEGMENT_GPIO_BOT_LEFT, 1);
    gpio_set_level(SEGMENT_GPIO_BOT_RIGHT, 1);
    gpio_set_level(SEGMENT_GPIO_POINT, 1);

    // Activer le latch correspondant
    gpio_set_level(latch_gpio, 1);  // Activer le latch
    vTaskDelay(1 / portTICK_PERIOD_MS); // Petit délai pour assurer la propagation
    gpio_set_level(latch_gpio, 0);  // Désactiver le latch

    // Activer les sorties si OUTPUT_ENABLE est utilisé
    gpio_set_level(OUTPUT_ENABLE, 0); // Activer les sorties (si OE est actif LOW)
}
