add_executable(unittest test.cpp)
target_link_libraries(unittest PRIVATE project_options project_warnings CONAN_PKG::catch2 CONAN_PKG::imagemagick)
