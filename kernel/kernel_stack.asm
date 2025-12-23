global kernel_stack_top

section .bss
align 16
kernel_stack_bottom:
    resb 16384
kernel_stack_top:
