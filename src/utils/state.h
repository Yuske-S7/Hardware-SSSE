#ifndef STATE_H
#define STATE_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>

typedef struct {
    int state;  // 0 : init, 1 : TEST, 2 : NORMAL
} program_state_t;

extern SemaphoreHandle_t state_mutex;
extern program_state_t program_state;

void program_state_init(void);

program_state_t program_state_get(void);

void program_state_set(int new_state);

#endif  // STATE_H
