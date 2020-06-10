#ifndef CLIARGS_H
#define CLIARGS_H

#include <docopt/docopt.h>
#include <fmt/format.h>
#include <variant>
#include <stdexcept>
#include <optional>
#include <Magick++.h>
#include <MagickCore/image.h>
#include <unordered_set>

const size_t DEFAULT_WIDTH = 60;
const std::unordered_set<std::string> filter_set = { "lanczos2",
    "lanczos3",
    "cubic",
    "linear",
    "nearest" };

struct Arguments
{
    std::string filename;
    std::string output_char = "▇";
    size_t width = DEFAULT_WIDTH;
    std::optional<size_t> height = std::nullopt;
    bool greyscale = false;
    std::string filter_type = "cubic";
};

const char USAGE[] =
    // TODO add filter arge
    R"(Img Print.
    Usage:
      img-print [-g] <filename> [--filtertype=<algorithm>]
      img-print [-g] <filename> <output-width> [--filtertype=<algorithm>]
      img-print [-g] <filename> <output-width> <output-height> [--filtertype=<algorithm>]
      img-print [-g] <filename> <output-width> <output-height> <output-character> [--filtertype=<algorithm>]
      img-print (-h | --help)

    Options:
      -h --help                 Show this screen.
      -g --greyscale            Output in greyscale
      --filtertype<algorithm>   Specify scaling algorithm option
                                  lanczos2
                                  lanczos3
                                  cubic
                                  linear
                                  nearest)";


inline auto get_args_map(int argc, char **argv)
{
    std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
        { argv + 1, argv + argc },
        true,// show help if requested
        "Img Print 1.0");// version string
    return args;
}

inline std::variant<Arguments, std::string> get_args(int argc, char **argv)
{

    size_t arg_position = 1;
    try
    {
        Arguments args;
        auto args_map = get_args_map(argc, argv);

        if (args_map["--filtertype"])
        {
            auto filter_str = args_map["--filtertype"].asString();
            if (filter_set.find(filter_str) != filter_set.end())
            {
                args.filter_type = filter_str;
            }
            else
            {
                fmt::print("{} is not a filtertype defaulted to cubic\n", filter_str);
            }
            arg_position++;
        }

        if (args_map["<filename>"])
        {
            args.filename = args_map["<filename>"].asString();
            arg_position++;
        }
        if (args_map["<output-width>"])
        {
            args.width = std::stoul(args_map["<output-width>"].asString());
            arg_position++;
        }

        if (args_map["<output-height>"])
        {
            args.height.emplace(std::stoul(args_map["<output-height>"].asString()));
            arg_position++;
        }
        args.greyscale = args_map["--greyscale"].asBool();
        if (args_map["<output-character>"])
        {
            args.output_char = args_map["<output-character>"].asString();
        }

        return std::variant<Arguments, std::string>(args);
    } catch (const std::invalid_argument &e)
    {
        return fmt::format(
            "Error: invalid argument \"\x1b[38;2;225;100;40m{}\x1b[0m\"\n", argv[arg_position]);
    }
}
#endif
