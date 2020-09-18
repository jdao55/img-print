#include "../src/img_print.hpp"
#include "../src/img_util.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    print_rgba(Data, Size, 1, "c");
    print_rgb(Data, Size, 1, "c");
    print_ga(Data, Size, 1, "c");
    print_g(Data, Size, 1, "c");
}
