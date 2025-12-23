global user_stack_top

section .bss
align 16
user_stack_bottom:
    resb 16384          ; 16 KB user stack
user_stack_top:
