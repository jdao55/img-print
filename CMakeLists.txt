cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(ray-tracer CXX)
include(cmake/StandardProjectSettings.cmake)
set (CMAKE_CXX_STANDARD 20)
# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" ON)
option(ENABLE_TESTING "Enable Test Builds" ON)
option(ENABLE_FUZZING "Enable Fuzz test Builds" OFF)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which
  # is a good idea if any #define's change
  target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

# Set up some extra Conan dependencies based on our needs
# before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

set(CONAN_EXTRA_REQUIRES  ${CONAN_EXTRA_REQUIRES})

include(cmake/Conan.cmake)
run_conan()

include(FindPkgConfig)
pkg_search_module(VIPSCPP REQUIRED IMPORTED_TARGET vips-cpp)


if(ENABLE_TESTING)
  enable_testing()
  message(
    "Building Tests"
  )
  add_subdirectory(test)
endif()


if(ENABLE_FUZZING)
  message(
    "Building fuzz Tests"
  )
  add_subdirectory(fuzztest)
endif()



add_subdirectory(src)
