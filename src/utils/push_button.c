#include "push_button.h"

static const gpio_num_t button_pins[] = {
    SECONDS_PUSHBUTTON_GPIO_PIN, MINUTES_PUSHBUTTON_GPIO_PIN,
    HOURS_PUSHBUTTON_GPIO_PIN, PLUS_PUSHBUTTON_GPIO_PIN,
    MINUS_PUSHBUTTON_GPIO_PIN};

static const char *button_names[] = {"Seconds push button",
                                     "Minutes push button", "Hours push button",
                                     "Plus push button", "Minus push button"};

static QueueHandle_t button_queue;

static void configure_buttons(const gpio_num_t *pins, size_t count) {
    uint64_t pin_bit_mask = 0;
    for (size_t i = 0; i < count; ++i) {
        pin_bit_mask |= (1ULL << pins[i]);
    }

    gpio_config_t io_conf = {.pin_bit_mask = pin_bit_mask,
                             .mode = GPIO_MODE_INPUT,
                             .pull_up_en = GPIO_PULLUP_ENABLE,
                             .pull_down_en = GPIO_PULLDOWN_DISABLE,
                             .intr_type = GPIO_INTR_DISABLE};
    gpio_config(&io_conf);
}

static bool are_buttons_pressed(const gpio_num_t *pins, size_t count,
                                TickType_t delay_ticks) {
    TickType_t start_time = xTaskGetTickCount();

    while ((xTaskGetTickCount() - start_time) < delay_ticks) {
        bool all_pressed = true;

        for (size_t i = 0; i < count; ++i) {
            if (gpio_get_level(pins[i]) != 0) {  // Bouton relâché
                all_pressed = false;
                break;
            }
        }

        if (!all_pressed) {
            return false;  // Si un bouton est relâché, sortir immédiatement
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // Petit délai pour éviter une
                                              // boucle trop rapide
    }

    return true;  // Tous les boutons sont restés appuyés pendant le délai
                  // spécifié
}

void simultaneous_button_task(void *pvParameters) {
    const gpio_num_t monitored_buttons[] = {HOURS_PUSHBUTTON_GPIO_PIN,
                                            MINUTES_PUSHBUTTON_GPIO_PIN,
                                            SECONDS_PUSHBUTTON_GPIO_PIN};
    size_t monitored_count =
        sizeof(monitored_buttons) / sizeof(monitored_buttons[0]);

    while (1) {
        if (are_buttons_pressed(monitored_buttons, monitored_count,
                                DELAY_MS / portTICK_PERIOD_MS)) {
            printf(
                "Hours, Minutes, and Seconds buttons pressed simultaneously "
                "for %d ms\n",
                DELAY_MS);
            // Action à effectuer lorsque les boutons sont détectés
        }

        vTaskDelay(50 / portTICK_PERIOD_MS);  // Délai entre les vérifications
    }
}

void trigger_timer() {
    configure_buttons(button_pins,
                      sizeof(button_pins) / sizeof(button_pins[0]));

    xTaskCreate(simultaneous_button_task, "Simultaneous Button Task", 4096,
                NULL, 10, NULL);
}
