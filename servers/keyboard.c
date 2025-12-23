#include "../ipc/ipc.h"
#include "../kernel/syscall.h"

static inline void sys_send(message_t* msg) {
    asm volatile("int $0x80" : : "a"(SYS_IPC_SEND), "b"(msg));
}

void keyboard_server() {
    message_t msg;

    while (1) {
        // Block waiting for key message (later)
        // For now: placeholder
    }
}
