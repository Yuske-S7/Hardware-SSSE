#include "test_mode.h"

void test_display() {

    for (int i = 0; i < get_latch_gpios_count(); i++) {
        segment_clean_all(get_latch_gpios()[i]);
    }

    for (int i = 0; i < get_latch_gpios_count(); i++) {
        segment_run_light(get_latch_gpios()[i]);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
        segment_clean_all(get_latch_gpios()[i]);

        segment_run_light(get_latch_gpios()[i]);
        vTaskDelay(DELAY_MS / portTICK_PERIOD_MS);
        segment_clean_all(get_latch_gpios()[i]);
    }
    vTaskDelete(NULL);
}

void test_push_button() {

}