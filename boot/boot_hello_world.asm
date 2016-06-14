;
; A simple boot sector that prints a message to the screen using a BIOS routine.
;
mov ah, 0x0e                 ; int 10/ ah = 0eh -> scrolling teletype BIOS routine
mov al, "H"
int 0x10
mov al, "e"
int 0x10
mov al, "l"
int 0x10
mov al, "l"
int 0x10
mov al, "o"
int 0x10
    
loop:                    ; Loop forever

    jmp loop
;
; Padding and magic BIOS number.
;

times 510-($-$$) db 0    ; Pad our file with 510 of zero bytes

dw 0xaa55                ; Add magic number to tell BIOS that is a boot sector
