from pathlib import Path
import sys

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("No input lib")
        exit()

    lib_name = sys.argv[1]
    print("Creating lib", lib_name)

    dir_path = Path(lib_name)
    dir_path.mkdir(exist_ok=True)

    dir_path = Path(lib_name + "/include/" + lib_name)
    dir_path.mkdir(exist_ok=True, parents=True)

    dir_path = Path(lib_name + "/src")
    dir_path.mkdir(exist_ok=True)

    dir_path = Path(lib_name + "/tests")
    dir_path.mkdir(exist_ok=True)

    f = open(lib_name + "/CMakeLists.txt", "w")
    f.write("cmake_minimum_required(VERSION 3.0)\n")
    f.write("project(" + lib_name + ")\n")

