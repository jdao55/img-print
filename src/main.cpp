#include <algorithm>
#include <fmt/format.h>

#include <cliargs.hpp>
#include <img_print.hpp>

template<class... Ts>
struct overload : Ts...
{
    using Ts::operator()...;
};
template<class... Ts>
overload(Ts...) -> overload<Ts...>;


int main(int argc, char **argv)
{

    const auto args = get_args(argc, argv);
    std::visit(overload{ [](const std::string &arg) { fmt::print("{}", arg); },
                   [](const Arguments &arg) { image_print(arg); } },
        args);
}
