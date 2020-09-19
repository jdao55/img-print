// #include "../src/img_print.hpp"
// #include "../src/img_util.hpp"
#include <cstdint>
#include <cstddef>
auto fuzztest(const uint8_t *Data, size_t Size)
{
    if (Size > 0)
        return Data[Size - 1];
    return uint8_t(0);
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) { fuzztest(Data, Size); }
