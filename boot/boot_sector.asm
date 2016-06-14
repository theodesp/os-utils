;
; A simple boot sector program
;

loop:                    ; Loop forever
                     
    jmp loop    
    
times 510-($-$$) db 0    ; Pad our file with 510 of zero bytes

dw 0xaa55                ; Add magic number to tell BIOS that is a boot sector
