#ifndef CLIARGS_H
#define CLIARGS_H

#include <docopt/docopt.h>
#include <fmt/format.h>


struct Arguments{
    std::string filename;
    size_t width = 50;
    size_t height = 25;
    bool greyscale = false;
};

const char USAGE[] =
    R"(Img Print.
    Usage:
      img-print -o [-g] <filename>
      img-print -d [-g] <output-width> <output-height> -o <filename>
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
    return args;
}

inline Arguments get_args(int argc, char **argv)
{
    Arguments args;
    auto args_map = get_args_map(argc, argv);
     for(auto const& arg : args_map) {
        std::cout << arg.first <<  arg.second << std::endl;
    }

     if(args_map["-o"].asBool())
    {
        args.filename = args_map["<filename>"].asString();

    }
     if(args_map["-d"].asBool())
    {
        args.width = std::stoul(args_map["<output-width>"].asString());
        args.height = std::stoul(args_map["<output-height>"].asString());
    }
     if(args_map["--greyscale"].asBool())
        args.greyscale = true;
    return args;
}
#endif
