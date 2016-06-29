;
; A simple boot sector that prints a message to the screen with the help of the stack.
;

mov ah, 0x0e 			 ; int 10/ ah = 0eh -> scrolling teletype BIOS routine
mov bp, 0x8000 			 ; Set the base of the stack a little above where BIOS starts 0x7x00
mov sp, bp				 ; Init sp

push 'O'				 ; Push some characters on the stack as 16 bit chars for later
push 'L'				 ; retrieval.
push 'L'
push 'E'
push 'H'

pop bx					 ; Note we can only pop 16 - bits , so pop to bx and print each char
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

pop bx
mov al, bl
int 0x10

mov al, [0x7ffe]		 ; This proves that the stack grows downwards from bp
int 0x10				 ; Print char at 0x8000 - 0x2

loop:                    ; Loop forever
    jmp loop
;
; Padding and magic BIOS number.
;

times 510-($-$$) db 0    ; Pad our file with 510 of zero bytes
dw 0xaa55                ; Add magic number to tell BIOS that is a boot sector
