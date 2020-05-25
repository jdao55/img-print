# img-print
Print images to 24 bit termials as text
 
![image created](sample_ouput.png?raw=true "") 
 
sample output
# Dependencies
- c++17 compiler
- CMake > 3.15
- Conan [install instructions](https://docs.conan.io/en/latest/installation.html)

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
Executable is found in 
```
build/bin/img-png
```
# Usage 
```
Usage:
  img-print [-g] <filename> [--filtertype=<algorithm>]
  img-print [-g] <filename> <output-width> [--filtertype=<algorithm>]
  img-print [-g] <filename> <output-width> <output-height> [--filtertype=<algorithm>]
  img-print [-g] <filename> <output-width> <output-height> <output-character> [--filtertype=<algorithm>]
  img-print (-h | --help)
Options:
   -h --help                   Show this screen.
   -g --greyscale              Output in greyscale
   --filtertype=<algorithm>    Specify scaling algorithm
                               options are:
                                   lanczos
                                   cubic
                                   quadratic
                                   catrom
                                   sinc
                   
```

## Options
```-h --help```          Print help message 
 
```-g --greyscale```   Output in greyscale
# Example
Tested with Konsole
 
![image created](example.png?raw=true "") 

# Running Tests
test Executable is found in 
```
build/bin/unittest
```
