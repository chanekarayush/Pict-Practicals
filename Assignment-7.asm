;Program to print the processor mode, gdtr contents, ldtr contents, idtr contents as well as TR, MSW and CPUID

;-----------------Data Section-----------------

statmsg db 10, "Processor status display", 0xa, 0xd
statmsglen equ $-statmsg

exitmsg db "Exited Program with exit code (0)", 0xa
exitmsglen equ $-exitmsg

cpumode1 db "Mode of the Processor : Protected Mode", 0xa, 0xd
cpumode1len equ $-cpumode1
cpumode2 db "Mode of the Processor: Real Mode", 0xa, 0xd
cpumode2len equ $-cpumode2
gdtrmsg db 10, "Contents of GDTR are: "
gdtrmsglen equ $-gdtrmsg
ldtrmsg db 10, "Contents of LDTR are: "
ldtrmsglen equ $-ldtrmsg
idtrmsg db 10, "Contents of IDTR are: "
idtrmsglen equ $-idtrmsg
trmsg db 10, "Contents of TR are: "
trmsglen equ $-trmsg
mswmsg db 10, "Contents of MSW are: "
mswmsglen equ $-mswmsg
cpustat db 10,10, "CPUID is: "
cpustatlen equ $-cpustat
nl db 0xa, 0xd
nlen equ $-nl

section .bss
gdtrcontent resb 6
ldtrcontent resb 2
idtrcontent resb 6
trcontent resb 2
mswcontent resb 4
d4save resb 4
vendorString resb 13

%macro rw 3
    mov rax, %1
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    syscall
%endmacro 

%macro exit 0
    mov rax, 60
    mov rdx, 0
    syscall
%endmacro

section .text 

global _start
_start: 
    rw 01, statmsg, statmsglen
    smsw eax

    bt eax, 0
    jc protec
    rw 01, cpumode2, cpumode2len
    exit

    protec:
        rw 01, cpumode1, cpumode1len

        sgdt [gdtrcontent]
        sldt [ldtrcontent]
        sidt [idtrcontent]
        str [trcontent]
        smsw [mswcontent]

;===========================GDTR Contents===========================
    rw 01, gdtrmsg, gdtrmsglen
    mov bx, [gdtrcontent + 4]
    call disp4

    mov bx, [gdtrcontent + 2]
    call disp4

    mov bx, [gdtrcontent]
    call disp4

;===========================LDTR Contents===========================
    rw 01, ldtrmsg, ldtrmsglen
    mov bx, [ldtrcontent]
    call disp4
;===========================IDTR Contents===========================
    rw 01, idtrmsg, idtrmsglen
    mov bx, [idtrcontent + 4]
    call disp4

    mov bx, [idtrcontent + 2]
    call disp4

    mov bx, [idtrcontent]
    call disp4
;=========================== TR Contents ===========================
    rw 01, trmsg, trmsglen
    mov bx, [ldtrcontent]
    call disp4
;========================== MSW Contents ===========================
    rw 01, mswmsg, mswmsglen

    mov bx, [mswcontent + 2]
    call disp4
    mov bx, [mswcontent]
    call disp4

;==========================CPUID Contents===========================

rw 01, cpustat, cpustatlen
mov dword[vendorString], 0
mov eax, 0
cpuid
mov dword[vendorString + 0], ebx
mov dword[vendorString + 4], edx
mov dword[vendorString + 8], ecx
rw 01, vendorString, 12
rw 01, nl, nlen
rw 01, nl, nlen
rw 01, exitmsg, exitmsglen
exit

disp4:  mov rdi, d4save
        mov rcx, 4

    stop1:  rol bx, 4
            mov al, bl 
            and al, 0FH
            cmp al, 09H
            jbe add_30
            add al, 7h

    add_30: add al, 30h
            mov [rdi], al 
            inc rdi 
            loop stop1
            rw 01, d4save, 4
            ret

