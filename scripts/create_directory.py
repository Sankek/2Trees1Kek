from pathlib import Path
import sys

if len(sys.argv) > 1:
    name = sys.argv[1]
    path = name
    Path(path).mkdir(parents=True, exist_ok=True)
else:
    print("Unable to create directory: path is not specified\n")

