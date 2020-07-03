
add_executable(img-print main.cpp img_print.cpp img_util.cpp)
target_compile_options(img-print PUBLIC ${libvips_CFLAGS_OTHER})
target_link_libraries(img-print PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt PkgConfig::VIPSCPP)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(img-print PRIVATE -Ofast -fconcepts-ts)
endif ()
