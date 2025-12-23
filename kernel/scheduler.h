#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "task.h"

void scheduler_init(void);
void scheduler_add(task_t* task);
void scheduler_start(void);
void scheduler_yield(void);

#endif
