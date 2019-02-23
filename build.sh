#!/bin/bash

# ASM Build
nasm -f bin -o boot.bios.bin boot.bios.asm

# GPT/ EFI Setup


# BIOS Setup
rm -rf iso
dd if=/dev/zero of=boot.bios.img bs=1024 count=1440
dd if=boot.bios.bin of=boot.bios.img seek=0 count=1 conv=notrunc
mkdir iso
mv boot.bios.img iso
genisoimage -V 'BOOT' -input-charset iso8859-1 -o boot.bios.iso -b boot.bios.img iso/
