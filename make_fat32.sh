dd if=/dev/zero of=fat32.img bs=1024 count=262144
mkfs.vfat -F 32 fat32.img
