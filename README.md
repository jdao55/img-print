# img-print
Print images to 24 bit termials as text(wip)
 
![image created](sample_ouput.png?raw=true "") 
 
sample output
# Dependencies
- c++17 compiler
- CMake > 3.15
- Conan

# Building
1. clone repository 
```
git clone https://github.com/jdao55/img-print.git && cd img-print
```
2. Create build directory and Run Cmake
```
mkdir build && cd build
cmake ../ 
```
3. Compile program
```
make -j4
```
# Usage 
```
img-print [-g] <filename>
img-print [-g] <filename> <output-width> <output-height>
img-print (-h | --help)
```

## Options
```-h --help```          Print help message 
 
```-g --greyscale```   Output in greyscale
# Example
![image created](example.png?raw=true "") 
