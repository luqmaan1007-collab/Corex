#!/bin/bash
# corex - compile .mycorex to LLVM IR → machine code → bootable binary

set -e

if [ $# -lt 1 ]; then
    echo "Usage: corex <file.mycorex> [output]"
    exit 1
fi

INPUT="$1"
OUTPUT="${2:-corex_os.bin}"

echo "[1/6] Lexing and Parsing..."
python3 lexer_parser.py "$INPUT" ast.json

echo "[2/6] Type Checking / Ownership..."
python3 type_checker.py ast.json checked_ast.json

echo "[3/6] Generate LLVM IR..."
python3 ir_generator.py checked_ast.json temp_corex.ll

echo "[4/6] Compile LLVM IR → Object..."
llc -filetype=obj temp_corex.ll -o temp_corex.o

echo "[5/6] Link Object → Bootable Binary..."
# linker.ld should contain your kernel entry point and memory layout
ld -T linker.ld -o "$OUTPUT" temp_corex.o

echo "[6/6] Runtime / Libraries Initialization..."
# Optional: include runtime object files
# e.g., ld -r temp_runtime.o temp_corex.o -o "$OUTPUT"

rm -f temp_corex.ll ast.json checked_ast.json temp_corex.o

echo "Done! Bootable binary: $OUTPUT"
