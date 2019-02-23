[BITS 16]

start:
  mov si, MSG
  call print_string
  jmp $

print_string:
  mov al,[si]
  or al,al
  jz  .end
  inc si
  call print_char
  jmp print_string
.end:
  retn

print_char:
  mov ah,0x0E
  mov bl,0x07
  mov bh,0x00
  int 0x10
  retn

  MSG db 'Hello World!',0x0A,0

TIMES 510 - ($ - $$) db 0
DW 0xAA55
