#!/bin/bash
nasm -f bin -o boot.bin boot.asm
rm -rf iso
dd if=/dev/zero of=boot.img bs=1024 count=1440
dd if=boot.bin of=boot.img seek=0 count=1 conv=notrunc
mkdir iso
mv boot.img iso
genisoimage -V 'BOOT' -input-charset iso8859-1 -o boot.iso -b boot.img iso/
