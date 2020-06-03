add_executable(unittest test.cpp ../src/img_print.cpp ../src/img_util.cpp)
target_link_libraries(unittest PRIVATE project_options project_warnings CONAN_PKG::catch2 CONAN_PKG::imagemagick CONAN_PKG::fmt CONAN_PKG::docopt.cpp)
