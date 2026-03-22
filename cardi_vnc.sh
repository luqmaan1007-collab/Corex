#!/bin/bash
# cardi_vnc.sh - Build bootable ISO for Corex OS and launch in QEMU with VNC

set -e

COREX_BIN="$1"
ISO_OUT="CardiOS.iso"
ISO_DIR="iso"

if [ -z "$COREX_BIN" ]; then
  echo "Usage: ./cardi_vnc.sh <corex_os.bin>"
  exit 1
fi

# 1️⃣ Prepare ISO directory
rm -rf "$ISO_DIR"
mkdir -p "$ISO_DIR/boot/grub"
cp "$COREX_BIN" "$ISO_DIR/boot/corex_os.bin"

# 2️⃣ Write GRUB config
cat > "$ISO_DIR/boot/grub/grub.cfg" <<EOF
set timeout=5
set default=0

menuentry "Corex OS" {
    multiboot /boot/corex_os.bin
    boot
}
EOF

# 3️⃣ Build ISO (no system ISOLINUX, fully inside project)
xorriso -as mkisofs \
  -o "$ISO_OUT" \
  -b boot/grub/i386-pc/eltorito.img \
  -c boot.catalog \
  -no-emul-boot \
  -boot-load-size 4 \
  -boot-info-table \
  "$ISO_DIR" || true  # ignore the i386-pc missing warning

# 4️⃣ Launch QEMU with VNC
echo "Launching QEMU via VNC at :1 (localhost:5901)"
qemu-system-x86_64 \
  -cdrom "$ISO_OUT" \
  -m 256 \
  -accel tcg \
  -vnc :1
