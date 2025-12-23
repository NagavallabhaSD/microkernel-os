#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef enum {
    TASK_READY,
    TASK_RUNNING,
    TASK_BLOCKED
} task_state_t;

typedef struct task {
    uint32_t esp;
    uint32_t stack_base;
    task_state_t state;
    struct task* next;
} task_t;

/* Task API */
task_t* task_create(void (*entry)(void));

#endif
