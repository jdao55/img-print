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

template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
template<class... Ts> overload(Ts...) -> overload<Ts...>;


int main(int argc, char **argv)
{

    auto args = get_args(argc, argv);
    std::visit(overload{ [](const std::string & arg) { fmt::print("{}", arg); },
                         [](Arguments & arg){image_print(arg);}
        }, args);
}
