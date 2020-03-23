add_executable(img-print main.cpp)
target_link_libraries(img-printray-tracer PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt CONAN_PKG::spdlog CONAN_PKG::imagemagick)
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(img-print PRIVATE -Ofast)
endif ()
