; program to find the largest of given byte/ dword/ word / 64 bit numbers <---*  

section .data
    arr db 0000000000000069h, 0000000000000018h, 0000000000000053h, 0000000000000091h, 0000000000000024h
    ; the array which I will be using (16 digits for each number)
    msg db "",0xa
    msglen equ $-msg

    msg2 db "The Greatest Number is:", 0xa
    msg2len equ $-msg2
    ipmsg db "The 5 64 bit numbers are: ", 0xa
	ip_len equ $ -ipmsg

section .bss
    ctr resb 1
    bigno resb 64

    %macro rw 3
		mov rax, %1
		mov rdi, %1
		mov rsi, %2
		mov rdx, %3
		syscall
	%endmacro rw

section .text
    global _start
    _start:	rw 01, ipmsg, ip_len    ; prompt to display elements of array
            mov byte[ctr], 05h
	        mov rbp, arr
    
    back2:	mov al, [rbp]           ;  displaying all 5 elements of the array
            Call display            ; converting hex to hex ascii and displaying
            inc rbp
            dec byte[ctr]
            jnz back2
    
    rw 01, msg2, msg2len			; output msg for greatest no.   
	mov byte[ctr], 05h
	mov rbp, arr				    ; moving contents of arr into rbp
	xor rax, rax        

    	; compare and if and else for greater or lesser		
	back:	cmp al, [rbp]
		    ja next
		    mov al, [rbp]
    
    next:	inc rbp
		    dec byte[ctr]
		    JNZ back
        
        call display
        
    mov rax,60
    mov rdi,0
    syscall

display: 	mov rbx, rax
            mov cx, 16
            mov rsi, bigno


    		backrotate:	Rol rbx,04H
                        mov al,bl
                        AND al,0FH
                        cmp al,09H
                        jg add_37
                        add al,30H
                        jmp skip

            add_37: 	add al,37

            skip:		mov byte[rsi],al
                        add rsi,01
                        dec cx
                        jnz backrotate
            
            rw 1, bigno, 64
  		    rw 1, msg, msglen
  		    ret

