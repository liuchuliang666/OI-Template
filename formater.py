import os
import os.path
path = os.getcwd()
for root, dirs, files in os.walk(path):
    for name in files:
        if (name.endswith(".cpp")):
            localpath = root + '/' + name
            print(localpath)
            os.system(f"clang-format -i {localpath} -style=File")