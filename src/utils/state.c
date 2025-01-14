#include "state.h"

program_state_t program_state;
SemaphoreHandle_t state_mutex;

void program_state_init(void)
{
    program_state.state = 0;
    
    state_mutex = xSemaphoreCreateMutex();
    if (state_mutex == NULL) {
        printf("Erreur : impossible de créer le mutex de l'état !\n");
    }
}

program_state_t program_state_get() {
    program_state_t state_copy;
    if (xSemaphoreTake(state_mutex, portMAX_DELAY) == pdTRUE) {
        state_copy = program_state;  // Copier l'état global
        xSemaphoreGive(state_mutex);
    }
    printf("get good\n");
    return state_copy;
}

void program_state_set(int new_state) {
    if (xSemaphoreTake(state_mutex, portMAX_DELAY) == pdTRUE) {
        program_state.state = new_state; // Modifier l'état global
        xSemaphoreGive(state_mutex);
    }
    printf("set good\n");
}