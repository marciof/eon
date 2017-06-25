%include "arg.asm"

%define STACK_LENGTH (16 * 1024)
extern c_main

section .bss
align 4

global _multiboot_info
_multiboot_info:
    resd 1

global _multiboot_magic_nr
_multiboot_magic_nr:
    resd 1

stack:
    resb STACK_LENGTH

section .text
align 4

global halt
halt:
    cli
    hlt

global main
main:
    ; The stack pointer initial value isn't "stack + STACK_LENGTH - 1" because
    ; it always points to the last element.
    mov esp, (stack + STACK_LENGTH)

    ; FIXME: don't use global state, pass as arguments
    mov [_multiboot_magic_nr], eax
    mov [_multiboot_info], ebx
    
    call c_main

global reset
reset:
    ; FIXME: explain part about keyboard.
    ; Reset by causing a triple fault (which doesn't require a keyboard).
    int 3
    ; FIXME: can reuse `halt`?
    cli
    hlt