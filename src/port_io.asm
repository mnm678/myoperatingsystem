global outb
global inb

section .text
bits 64

;outb(port, 2byte)
;outb:

;out si, di

;ret

;inb(port) returns 2byte
;inb:

;in ax, di
;in ax, 0x64

;ret

