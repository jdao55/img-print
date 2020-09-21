if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

add_executable(unittest test.cpp ../src/img_print.cpp )

target_compile_options(unittest PUBLIC ${libvips_CFLAGS_OTHER} )
target_link_libraries(unittest PRIVATE project_options project_warnings CONAN_PKG::catch2 CONAN_PKG::fmt CONAN_PKG::docopt.cpp  PkgConfig::VIPSCPP)

catch_discover_tests(unittest)

