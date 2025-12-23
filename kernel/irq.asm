global irq1_handler
extern keyboard_irq
extern pic_send_eoi

irq1_handler:
    pusha
    call keyboard_irq
    push dword 1
    call pic_send_eoi
    add esp, 4
    popa
    iret
