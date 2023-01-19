# A command line selection tool for the terminal

Modify the grub.cfg file to select the next time default boot entry.

# Usage:
```
./dual-boot-helper <PATH_TO_GRUB_CFG>
```

and it will print the current default boot entry and a list of all boot entries. Then it will ask you to select a new default boot entry.

# Example:
```
./dual-boot-helper /boot/grub/grub.cfg
Current default boot entry: 0
0: Windows Boot Manager
1: Ubuntu
Select new default boot entry: 1
Selected: Ubuntu
Done.
```

# How to build:
```
mkdir build
cd build
cmake .. -G Ninja -DCMAKE_LINKER=mold -DCMAKE_BUILD_TYPE=Release
ninja
```

# Dependencies:
- C++20
- CMake
- Ninja
- mold
- nlohmann/json

# License:
GPLv3

