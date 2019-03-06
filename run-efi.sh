mkdir -p $PWD/build/tmp
BASE_DIR=$PWD/build/tmp
EFI_DIR=$PWD/build/efi-kern
rm -rf $BASE_DIR/qos.img

los=$(losetup -l | grep qos.img | awk -e '{ print$1; exit }')
if [ $(echo $los | wc -l) -gt 0 ]; then
  for device in $los; do
    losetup -d $device
  done
fi

dd if=/dev/zero of=$BASE_DIR/qos.img bs=1024 count=262144
parted --script $BASE_DIR/qos.img mklabel msdos mkpart p fat32 1 200 set 1 boot on
mkfs.vfat -F 32 $BASE_DIR/qos.img
kpartx -a $BASE_DIR/qos.img

los=$(losetup -l | grep qos.img | awk -e '{ print$1; exit }') 

echo "Mapping $BASE_DIR/qos.img to device"
echo "Device is $los"

if [ ! -f /mnt/qos ]; then
  mkdir -p /mnt/qos
  echo "Made mount point /mnt/qos"
fi

mount $los /mnt/qos 
echo "Mounted to /mnt/qos, contents in $BASE_DIR/qos.img fs:"
mkdir -p /mnt/qos/EFI/BOOT
cp $EFI_DIR/bootx64.efi /mnt/qos/EFI/BOOT/bootx64.efi
tree /mnt/qos
umount /mnt/qos

qemu-system-x86_64 -enable-kvm -m 4096 -cpu host -drive if=pflash,format=raw,readonly,file=/usr/share/edk2.git/ovmf-x64/OVMF-pure-efi.fd $BASE_DIR/qos.img
if [ ! -z $KEEP ]; then
  rm -rf $PWD/build/tmp   
fi 
