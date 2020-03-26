#include <docopt/docopt.h>
#include <fmt/format.h>


const char USAGE[] =
    R"(Img Print.
    Usage:
      img-print -o <filename>
      img-print -d <output-width> <output-height> -o <filename>
      img-print (-h | --help)

    Options:
      -h --help          Show this screen.
      -g --greyscale    Output in greyscale)";


inline auto get_args_map(int argc, char **argv)
{
    std::map<std::string, docopt::value> args
        = docopt::docopt(USAGE,
                         { argv + 1, argv + argc },
                         true,               // show help if requested
                         "Img Print 1.0");  // version string
    // for(auto const& arg : args) {
    //     std::cout << arg.first <<  arg.second << std::endl;
    // }
    return args;
}

void set_args(std::map<std::string, docopt::value>& arg_map, size_t & width, size_t &height, std::string & file_name)
{
    if(arg_map["-o"])
    {
        file_name = arg_map["<filename>"].asString();

    }
    if(arg_map["-d"])
    {
        width = std::stoul(arg_map["<output-width>"].asString());
        height = std::stoul(arg_map["<output-height>"].asString());
    }
}
