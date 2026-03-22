#!/bin/bash
# cardi.sh - run .corex files using Corex interpreter

set -e

if [ $# -lt 1 ]; then
    echo "Usage: ./cardi.sh <file.corex>"
    exit 1
fi

COREX_FILE="$1"
SYNTAX_FILE="CorexSyntaxes/corexsyntax.json"

# Optional: output binary name for special builds
OUTPUT="${2:-corex_output.bin}"

# Run Corex interprete./corex "$COREX_FILE" "$SYNTAX_FILE" "$OUTPUT"
