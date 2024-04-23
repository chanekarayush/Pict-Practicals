; program to show arithmetic operation on 64 bit nos. (+,-,*,/) using procedures. 
; switch case menu driven program. 
section .data
    menumsg db "Select the operation you want: ", 0xa
    menumsglen equ $- menumsg

    menu db "1. Addition, 2. Subtraction, 3. Multiplication, 4. Division, 5. Exit", 0xa
    menulen equ $- menu

    resmsg db "The result of your operation is: ", 0xa
    resmsglen equ $-resmsg

    msg db "", 0xa, 0xd
    msglen equ $- msg

    op1 db 02h
    op2 db 06h
;-------------------------------------------------------------------------------
section .bss
    res resb 64
    bigno resb 64
    ipch resb 1

    %macro rw 3
        mov rax, %1
        mov rdi, %1
        mov rsi, %2
        mov rdx, %3
        syscall
    %endmacro rw

    %macro exit 0
        mov rax, 60
        mov rdi, 0
        syscall
    %endmacro exit
;-------------------------------------------------------------------------------

section .text 

global _start
    _start: rw 01, menumsg, menumsglen
            rw 01, menu, menulen

            rw 00, ipch, 01             ; taking choice from user

            ; Addition
            cmp byte[ipch], '1'
            je addno

            ; Subtraction
            cmp byte[ipch], '2'
            je subno

            ; Multiplication
            cmp byte[ipch], '3'
            je mulno

            ; Division
            cmp byte[ipch], '4'
            je divno

            cmp byte[ipch], '5'
            je esc

            jmp _start

addno:  rw 01, resmsg, resmsglen 
        call addition
        jmp _start
;call addition procedure here

subno:  rw 01, resmsg, resmsglen 
        call subtraction
        jmp _start  
;sub process

mulno:  rw 01, resmsg, resmsglen 
        call multiplication
        jmp _start  
; mul process

divno:  rw 01, resmsg, resmsglen 
        call division
        jmp _start
        ; div process

esc:    exit        ; exit macro called
;-------------------------------------------------------------------------------

;----------Procedures----------

addition:   xor rax, rax
            mov al, [op1]
            add al, [op2]
            call display
            ret             ; important i forgort lol

subtraction:    xor rax,rax
                mov ax, [op2]
                sub ax, [op1]
                mov ah, 00h
                call display 
                ret 

multiplication: xor rax, rax
                xor rcx, rcx
                mov ax, word[op1]
                mov cx, word[op2]
                mul cx 
                call display
                ret

division:   xor rax, rax
			xor rcx, rcx
            mov al, byte[op2]
            mov cl, byte[op1]
            div cl
            call display

            ; logic to show remainder
            mov cl, ah
            mov al, cl
            call display
            ret

display:mov rbx, rax		; basically converts the number from hex to ascii-hex and prints it.
		mov cx, 16		    ; counter
		mov rsi, bigno		; store bigno to rsi (hex values -> ascii)

	backrotate:	Rol rbx,04H
			 	mov al,bl
			 	AND al,0FH
			 	cmp al,09H
			 	jg add_37
			 	add al,30H
		 		jmp skip
	   
	add_37: 	add al,37
	   	
	skip:	mov byte[rsi],al
			add rsi,01
			dec cx
			jnz backrotate

	rw 1, bigno, 64
	rw 1, msg, msglen
	ret
   