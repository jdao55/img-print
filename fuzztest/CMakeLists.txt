add_executable(fuzz_tester fuzztest.cpp)
target_link_libraries(
 fuzz_tester PRIVATE
 project_options
 project_warnings
 CONAN_PKG::docopt.cpp
 CONAN_PKG::fmt
 #PkgConfig::VIPSCPP
 -coverage
 -fsanitize=fuzzer,undefined,address)
target_compile_options(fuzz_tester PRIVATE -fsanitize=fuzzer,undefined,address )


set(FUZZ_RUNTIME
 5
 CACHE STRING "run fuzz tests for 5 sec"
 )
add_test(NAME fuzz_test_run COMMAND fuzz_tester -max_total_time${FUZZ_RUNTIME})
