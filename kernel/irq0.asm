global irq0_handler
extern pic_send_eoi

irq0_handler:
    pusha
    push dword 0
    call pic_send_eoi
    add esp, 4
    popa
    iret
