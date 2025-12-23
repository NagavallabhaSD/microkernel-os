global tss_flush

tss_flush:
    mov ax, 0x2B   ; TSS selector (5 * 8 | 3)
    ltr ax
    ret
