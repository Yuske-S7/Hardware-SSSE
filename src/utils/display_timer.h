#ifndef DISPLAY_TIMER_H
#define DISPLAY_TIMER_H

#include "push_button.h"

struct dtime {
    unsigned hours;
    unsigned minutes;
    unsigned seconds;
};

void save_dtime(struct dtime *dt);
void simultaneous_button_time_setting(void *pvParameters, struct dtime *dt);

#endif  // DISPLAY_TIMER_H
