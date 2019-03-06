set(intermobj efi.o)
set(outso efi.so)
set(boot bootx64.efi)
set(linker_script /usr/lib64/gnuefi/elf_${ARCH}_efi.lds)
set(link_flags -nostdlib -znocombreloc -T ${linker_script} -shared -Bsymbolic -L /usr/lib64 -L /usr/lib64/gnuefi /usr/lib64/gnuefi/crt0-efi-${ARCH}.o ${CMAKE_BINARY_DIR}/efi-kern/${intermobj} -lefi -lgnuefi)
set(elf_sections
	-j .text
	-j .sdata
	-j .data
	-j .dynamic
	-j .dynsym
	-j .rel
	-j .rela
	-j .reloc)

add_custom_target(${intermobj} ALL
        COMMAND ${CMAKE_C_COMPILER}
        -isystem /usr/include/efi 
        -isystem /usr/include/efi/x86_64 
        -isystem /usr/include/efi/protocol  
        -fno-stack-protector 
        -fpic -fshort-wchar -mno-red-zone 
        -Wall -o ${CMAKE_BINARY_DIR}/efi-kern/${intermobj} 
        -c /src/efi-kern/main.c
)
add_custom_target(${outso} ALL 
    COMMAND ${CMAKE_LINKER} 
    ${link_flags} -o ${CMAKE_BINARY_DIR}/efi-kern/${outso}
    DEPENDS ${intermobj})
add_custom_target(${boot} ALL 
    COMMAND objcopy 
    ${elf_sections}
    --target=efi-app-${ARCH}
    ${CMAKE_BINARY_DIR}/efi-kern/${outso}
    ${CMAKE_BINARY_DIR}/efi-kern/${boot}
    DEPENDS ${outso})
