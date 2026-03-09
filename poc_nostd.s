section .text

struct Timespec
    .duration resq 1
    .rem      resq 1
endstruc 

global _start
_start:
    mov rdi, 99999
    mov rax, 35
    syscall
    mov rdi, 5
    mov rax, 60
    syscall
