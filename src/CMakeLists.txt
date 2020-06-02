add_executable(img-print main.cpp img_print.cpp img_util.cpp)
target_link_libraries(img-print PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt CONAN_PKG::imagemagick)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(img-print PRIVATE -Ofast)
endif ()
