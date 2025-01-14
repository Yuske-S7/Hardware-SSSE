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

static void check_button_press(const gpio_num_t pin, const char *name) {
    if (gpio_get_level(pin) == 0) {
        // Envoyer le GPIO dans la queue
        if (button_queue != NULL) {
            if (xQueueSend(button_queue, &pin, 0) == pdTRUE) {
                printf("%s: (GPIO %d) pressed, sent to queue\n", name, pin);
            } else {
                printf("Queue full! Could not enqueue button press.\n");
            }
        }
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

void button_task(void *pvParameters) {
    const gpio_num_t *pins = (gpio_num_t *)pvParameters;
    size_t count = sizeof(button_pins) / sizeof(button_pins[0]);

    while (1) {
        for (size_t i = 0; i < count; ++i) {
            check_button_press(pins[i], button_names[i]);
        }
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void button_consumer_task(void *pvParameters) {
    gpio_num_t pressed_pin;

    while (1) {
        if (xQueueReceive(button_queue, &pressed_pin, portMAX_DELAY) ==
            pdTRUE) {
            printf("Button press processed for GPIO %d\n", pressed_pin);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}

void trigger_timer() {
    configure_buttons(button_pins,
                      sizeof(button_pins) / sizeof(button_pins[0]));

    button_queue = xQueueCreate(10, sizeof(gpio_num_t));
    if (button_queue == NULL) {
        printf("Failed to create button queue\n");
        return;
    }

    xTaskCreate(button_task, "Button Task", 4096, (void *)button_pins, 10,
                NULL);
    xTaskCreate(button_consumer_task, "Button Consumer Task", 4096, NULL, 10,
                NULL);
}
