include(CheckIPOSupported)

add_executable(img-print main.cpp img_print.cpp img_util.cpp)
target_link_libraries(img-print PRIVATE project_options project_warnings CONAN_PKG::docopt.cpp
  CONAN_PKG::fmt CONAN_PKG::imagemagick)

check_ipo_supported(RESULT lto_support OUTPUT error LANGUAGES CXX)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(img-print PRIVATE -Ofast)
  #add lto to release build
  if(lto_support)
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET img-print PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  else()
    message(STATUS "IPO / LTO not supported: <${error}>")
  endif()
endif ()
