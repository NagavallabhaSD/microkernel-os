#include "task.h"
#include "scheduler.h"

#define STACK_SIZE 4096

static uint8_t stacks[4][STACK_SIZE];
static int stack_index = 0;

task_t* task_create(void (*entry)(void)) {
    if (stack_index >= 4)
        return 0;

    task_t* task = (task_t*)&stacks[stack_index][0];
    uint32_t stack_top = (uint32_t)&stacks[stack_index][STACK_SIZE];

    uint32_t* stack = (uint32_t*)stack_top;

    *(--stack) = 0x0;              // fake return
    *(--stack) = (uint32_t)entry;  // EIP
    *(--stack) = 0x200;            // EFLAGS (IF = 1)

    task->esp = (uint32_t)stack;
    task->stack_base = (uint32_t)&stacks[stack_index][0];
    task->state = TASK_READY;
    task->next = 0;

    scheduler_add(task);
    stack_index++;

    return task;
}
