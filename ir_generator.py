import sys
with open(sys.argv[1]) as f:
    ast = f.read()
with open("temp_corex.ll", "w") as f:
    f.write("; LLVM IR stub\n")
    f.write(f"; Original AST length: {len(ast)}\n")
