# How OS Works

## Booting
Booting sequence goes ->
  BIOS or UEFI
    (Assuming UEFI)
      -> Boot GPT (UEFI)
        -> GPT will have a GPT Header which
            informs UEFI how partitions are broken down into LBA (Logical Block Allocators)
        -> Using the GPT Partition Entry Array, locate the first useable LBA block.
            The Entry in the Partition array describes the type of file system...
              along with the size and LBA Range.
        -> UEFI, using the GUID of the entry partition array, will know how to load the filesystem
            and hand over control.
        -> Filesystem is loaded from UEFI and control is handed over to the bootloader. In linux
            filesystems.  
      -> Boot MBR (BIOS)
