#include "syscall.h"
#include "../ipc/ipc.h"
#include "../ipc/ipc.h"

typedef struct {
    unsigned int edi, esi, ebp, esp;
    unsigned int ebx, edx, ecx, eax;
} regs_t;

void syscall_dispatch(regs_t* regs) {
    switch (regs->eax) {
        case SYS_IPC_SEND:
            ipc_send((message_t*)regs->ebx);
            ipc_debug_dump((message_t*)regs->ebx);
            break;

        default:
            break;
    }
}
