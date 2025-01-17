#ifndef DISPLAY_TIMER_H
#define DISPLAY_TIMER_H

#include "push_button.h"
#include "segments.h"

struct dtime {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
};

void save_dtime_hours(struct dtime *dt, bool is_increment);
void simultaneous_button_time_setting(void *pvParameters, struct dtime *dt);
void save_dtime_minutes(struct dtime *dt, bool is_increment);
void save_dtime_seconds(struct dtime *dt, bool is_increment);
void detect_h_button_task(void *pvParameters);
void print_time_display(struct dtime *dt);
void clock_increment(struct dtime *dt);

#endif  // DISPLAY_TIMER_H
