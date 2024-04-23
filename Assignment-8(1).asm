; Memory Block tranfer with string instructions & non string instructions, 
; block containing data can be specified in the data segment.

;------------Data Section-----

srcblock db 01h , 02h , 03h , 04h , 05h
; dstblock db 00h , 00h , 00h , 00h , 00h

menumsg db "Enter Choice: ", 10, '1. For Non String Operation', 10, '2. String Operations', 10
menulen equ $-menumsg

opmsg1 db "Contents of src block:", 10
opmsg1len equ $-opmsg1
opmsg2 db "Contents of dest block before transfer", 10
opmsg2len equ $-opmsg2
opmsg3 db "Contents of dest block after transfer", 10
opmsg3len equ $-opmsg3


;------------------BSS Section------------------

section .bss 

dstblock resb 5
ans resb 2
ctr resb 1

;-----------------macros-------------------------

%macro rw 3
    mov rax, %1
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    Syscall
%endmacro

%macro printarray 2                 
    mov rsi, %1                     
    mov byte[ctr], %2           

    %%repeat:                        
    mov al, [rsi]                   
    push rsi                        
    call display              
    rw 1, ans,2                    
    mov byte[ans] , 10              
    rw 1,ans,1                    
    pop rsi                         
    inc rsi                         
    dec byte[ctr]               
    jnz %%repeat                     
%endmacro

%macro exit 0
    mov rax, 60
    mov rdx, 00
    Syscall
%endmacro

;--------------Text Section----------------

section .text
global _start
_start: rw 01, opmsg1, opmsg1len
        printarray srcblock, 5

        rw 01, opmsg2, opmsg2len
        printarray dstblock, 5

        call transferwostr
        rw 01, opmsg3, opmsg3len
        printarray dstblock, 5
        
        call transferwstr
        rw 01, opmsg3, opmsg3len
        printarray dstblock, 5
        

    exit

;------------Procedures--------------

transferwostr:  
    mov rsi, srcblock         
    mov rdi, dstblock                 
    mov byte[ctr] ,05           
    again:  
        mov bl, [rsi]                   
        mov [rdi], bl                   
        inc rsi                        
        inc rdi                         
        dec byte[ctr]              
        jnz again                      
    ret   
               
transferwstr:   mov rsi, srcblock
                mov rdi, dstblock
                mov rcx, 05h

                cld
                rep movsb
                ret 

display: mov bl, al	    
        mov rcx, 2		
	    mov rbp, ans
	backrotate:	
            rol bl,04H
		 	mov dl,bl
		 	AND dl,0FH
		 	cmp dl,09H
		 	jbe add_30
		 	add dl,7H
	add_30: add dl,30H

	    	mov [rbp],dl
			inc rbp
			dec rcx
			jnz backrotate
	ret
    
