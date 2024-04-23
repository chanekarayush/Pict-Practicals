; Find the length of the input string by user

section .data
    ipmsg db "Enter a string", 0xa
	ipmsglen equ $-ipmsg
    opmsg db "The length of the string is: "
	opmsglen equ $-opmsg
    nl db "", 0xa
    nlen equ $-nl

section .bss
    str1 resw 100       ; string whose length is to be found

    result resb 50      ; length of str1 ka variable
    ctr resb 1          ; counter

    %macro rw 3             ; 3 args -> 1, 2, 3
		mov rax, %1
		mov rdi, %1
		mov rsi, %2
		mov rdx, %3
		syscall
	%endmacro rw

section .text
    global _start
    _start: rw 01, ipmsg, ipmsglen
            rw 00, str1, 100
            mov rbx, rax
            mov byte[ctr], 16
            mov rbp, result

            back:	rol rbx,04H  
                    mov al,bl
                    AND al,0FH
                    cmp al,09H
                    jg add_37
                    add al, 30H
                    jmp skip 
            
            add_37: add al, 37H

            skip:   mov byte[rbp],al
                    add rbp,01
                    dec byte[ctr]
                    jnz back

            rw 01, opmsg, opmsglen
            rw 01, result, 16
            rw 01, nl, nlen

            
            mov rax, 60
            mov rdi, 0
            syscall

