; Accept 5 numbers and Print them
;----------------------------------------------------
section .data
ipmsg db "Enter 5 64bit numbers: ", 0xa
ipmsglen equ $-ipmsg

opmsg db "This is the trash you entered", 0xa

opmsglen equ $-opmsg
;----------------------------------------------------
section .bss 
arr resb 100
ctr resb 1
;----------------------------------------------------
section .text

global _start

    _start: mov rax, 1 
            mov rdi, 1
            mov rsi, ipmsg
            mov rdx, ipmsglen
            syscall                             ; writing the input message

            mov byte[ctr], 05
            mov rbp, arr 

            input_label:mov rax, 0              ; accepting the elements of array from the user
                        mov rdi, 0
                        mov rsi, rbp
                        mov rdx, 17
                        syscall

                        add rbp, 17
                        dec byte[ctr]
                        jnz input_label

            mov byte[ctr], 05
            mov rbp, arr

            mov rax, 1                          ; writing the ouput message
            mov rdi, 1
            mov rsi, opmsg
            mov rdx, opmsglen
            syscall

           output_label:mov rax, 1              ; printing the elements of the array 
                        mov rdi, 1
                        mov rsi, rbp
                        mov rdx, 17
                        syscall

                        add rbp, 17
                        dec byte[ctr]
                        jnz output_label
;----------------------------------------------------
            mov rax, 60
            xor rdi, rdi
            syscall

