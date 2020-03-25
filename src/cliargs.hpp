#include <docopt/docopt.h>
#include <fmt/format.h>


const char USAGE[] =
    R"(Img Print.
    Usage:
      img-print -o <filename>
      img-print -d <char width> <char height> -o <filename> [<text ratio h:w>]
      img-print (-h | --help)

    Options:
      -h --help     Show this screen.)";

inline void help()
{
    fmt::print(R"(Img Print.
    Usage:
      img-print <char width> <char height> <filename> [<text ratio h:w>]
      img-print (-h | --help)

    Options:
      -h --help     Show this screen.)");

}

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

void set_var(std::map<std::string, docopt::value>& arg_map, size_t & width, size_t &height, std::string & file_name)
{
    if(arg_map["-o"])
    {
        file_name = arg_map["<filename>"].asString();

    }
    if(arg_map["-d"])
    {
        width = std::stoul(arg_map["<char width>"].asString());
        height = std::stoul(arg_map["<char height>"].asString());
    }
}
