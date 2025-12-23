#include "ipc.h"

static message_t msg_queue[MAX_MSG];
static int msg_count = 0;

void ipc_init() {
    msg_count = 0;
}

int ipc_send(message_t* msg) {
    if (msg_count >= MAX_MSG) return -1;
    msg_queue[msg_count++] = *msg;
    return 0;
}

int ipc_receive(int receiver, message_t* out) {
    for (int i = 0; i < msg_count; i++) {
        if (msg_queue[i].receiver == receiver) {
            *out = msg_queue[i];

            for (int j = i; j < msg_count - 1; j++)
                msg_queue[j] = msg_queue[j + 1];

            msg_count--;
            return 0;
        }
    }
    return -1;
}

void ipc_debug_dump(message_t* msg) {
    volatile char* v = (volatile char*)0xB8000;
    for (int i = 0; msg->data[i]; i++) {
        v[i * 2] = msg->data[i];
        v[i * 2 + 1] = 0x07;
    }
}
