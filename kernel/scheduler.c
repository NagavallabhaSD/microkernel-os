#include "scheduler.h"

static task_t* current = 0;
static task_t* task_list = 0;

extern void context_switch(uint32_t* old_esp, uint32_t new_esp);

void scheduler_init() {
    current = 0;
    task_list = 0;
}

void scheduler_add(task_t* task) {
    task->next = task_list;
    task_list = task;
}

void scheduler_start() {
    if (!task_list)
        return;

    current = task_list;
    current->state = TASK_RUNNING;

    asm volatile(
        "mov %0, %%esp\n"
        "ret\n"
        :
        : "r"(current->esp)
    );
}

void scheduler_yield() {
    if (!current || !current->next)
        return;

    task_t* prev = current;
    current = current->next;

    context_switch(&prev->esp, current->esp);
}
