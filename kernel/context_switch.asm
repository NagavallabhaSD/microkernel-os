global context_switch

context_switch:
    mov eax, [esp + 4]   ; &old_esp
    mov [eax], esp       ; save current ESP

    mov esp, [esp + 8]   ; load new ESP
    ret
