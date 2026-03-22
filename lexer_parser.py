import sys, json
with open(sys.argv[1]) as f:
    code = f.read()
with open(sys.argv[2], "w") as f:
    json.dump({"ast": code}, f)
