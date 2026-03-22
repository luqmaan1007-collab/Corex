#!/bin/bash
set -e

if [ $# -lt 1 ]; then
    echo "Usage: ./cardi_iso.sh <corex kernel file>"
    exit 1
fi

INPUT="$1"
OUTPUT_ISO="CardiOS.iso"
ISO_DIR="iso"

# Make the ISO folder
rm -rf "$ISO_DIR"
mkdir -p "$ISO_DIR"

# Copy your Corex kernel into it
cp "$INPUT" "$ISO_DIR/corex_os.bin"

# Create ISO with xorriso (no bootloader needed)
xorriso -as mkisofs -o "$OUTPUT_ISO" "$ISO_DIR"

echo "Done! ISO created: $OUTPUT_ISO"
