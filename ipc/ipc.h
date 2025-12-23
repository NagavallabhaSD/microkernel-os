#ifndef IPC_H
#define IPC_H

#include <stdint.h>

#define MAX_MSG 32

#define KERNEL_ID   0
#define CONSOLE_ID  1
#define KEYBOARD_ID 2

#define MSG_KEYBOARD 1

typedef struct {
    int sender;
    int receiver;
    int type;
    int data[4];
} message_t;

/* IPC API — MUST match ipc.c */
void ipc_init(void);
int ipc_send(message_t* msg);
int ipc_receive(int receiver, message_t* out);
void ipc_debug_dump(message_t* msg);

#endif
