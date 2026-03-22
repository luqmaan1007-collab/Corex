import sys, json
with open(sys.argv[1]) as f:
    ast = json.load(f)
with open(sys.argv[2], "w") as f:
    json.dump(ast, f)
