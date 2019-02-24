#!/bin/bash
genisoimage -v -J -r -V "TEST" \
        -o fat32.iso \
        -eltorito-alt-boot fat32.img
        -no-emul-boot .
