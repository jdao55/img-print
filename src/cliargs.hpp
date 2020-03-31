#ifndef CLIARGS_H
#define CLIARGS_H

#include <docopt/docopt.h>
#include <fmt/format.h>


struct Arguments
{
    std::string filename;
    std::string output_char = "\u2587";
    size_t width = 50;
    size_t height = 25;
    bool greyscale = false;
};

const char USAGE[] =
    R"(Img Print.
    Usage:
      img-print [-g] <filename>
      img-print [-g] <filename> <output-width> <output-height>
      img-print [-g] <filename> <output-width> <output-height> <output-character>
      img-print (-h | --help)

    Options:
      -h --help          Show this screen.
      -g --greyscale     Output in greyscale)";


inline auto get_args_map(int argc, char **argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        { argv + 1, argv + argc },
        true,// show help if requested
        "Img Print 1.0");// version string
    return args;
}

inline Arguments get_args(int argc, char **argv)
{
    Arguments args;
    auto args_map = get_args_map(argc, argv);
    if (args_map["<filename>"]) { args.filename = args_map["<filename>"].asString(); }
    if (args_map["<output-width>"] && args_map["<output-height>"])
    {
        args.width = std::stoul(args_map["<output-width>"].asString());
        args.height = std::stoul(args_map["<output-height>"].asString());
    }
    args.greyscale =  args_map["--greyscale"].asBool();
    if (args_map["<output-character>"]) { args.output_char = args_map["<output-character>"].asString(); }
    return args;
}
#endif
