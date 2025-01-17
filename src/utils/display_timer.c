#include "display_timer.h"

#define DISPLAY_TIMER_INTERVAL_MS 300

void save_dtime_hours(struct dtime *dt, bool is_increment) {
    if (is_increment) {
        dt->hours = (dt->hours + 1) % 24;
    } else {
        if (dt->hours == 0) {
            dt->hours = 23;
        } else {
            dt->hours--;
        }
    }
}

void save_dtime_minutes(struct dtime *dt, bool is_increment) {
    if (is_increment) {
        dt->minutes = (dt->minutes + 1) % 60;
    } else {
        if (dt->minutes == 0) {
            dt->minutes = 59;
        } else {
            dt->minutes--;
        }
    }
}

void save_dtime_seconds(struct dtime *dt, bool is_increment) {
    if (is_increment) {
        dt->seconds = (dt->seconds + 1) % 60;
    } else {
        if (dt->seconds == 0) {
            dt->seconds = 59;
        } else {
            dt->seconds--;
        }
    }
}

void print_time_display(struct dtime *dt) {
    const int *latches = get_latch_gpios();

    segment_display_digit(latches[5], dt->hours / 10);
    segment_display_digit(latches[4], dt->hours % 10);

    segment_display_digit(latches[3], dt->minutes / 10);
    segment_display_digit(latches[2], dt->minutes % 10);

    segment_display_digit(latches[1], dt->seconds / 10);
    segment_display_digit(latches[0], dt->seconds % 10);
}

void clock_increment(struct dtime *dt) {
    if (dt->seconds != 59) {
        save_dtime_seconds(dt, true);
    } else if (dt->minutes != 59) {
        save_dtime_minutes(dt, true);
        dt->seconds = 0;
    } else {
        save_dtime_hours(dt, true);
        dt->seconds = 0;
        dt->minutes = 0;
    }
}