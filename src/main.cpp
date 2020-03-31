#include <Magick++.h>
#include <MagickCore/image.h>
#include <algorithm>
#include <fmt/format.h>
#include <cstdint>
#include <map>
#include <docopt/docopt.h>
#include <iostream>

#include "cliargs.hpp"
#include "img_print.hpp"



int main(int argc, char **argv)
{

    Magick::InitializeMagick(*argv);
    auto args = get_args(argc, argv);
    image_print(args);
}
