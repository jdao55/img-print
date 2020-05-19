#ifndef CLIARGS_H
#define CLIARGS_H

#include <docopt/docopt.h>
#include <fmt/format.h>
#include <variant>
#include <stdexcept>
#include <optional>
#include <Magick++.h>
#include <MagickCore/image.h>
#include <unordered_map>

const size_t DEFAULT_WIDTH = 60;
const unordered_map<std::string, Magick::FilterType> filter_map {
    {"lanczos", Magick::LanczosFilter},
    {"cubic", Magick::CubicFilter},
    {"quadratic", Magick::QuadraticFilter},
    {"catrom", Magick::CatromFilter},
    {"sinc", Magick::SincFilter}
}

struct Arguments
{
    std::string filename;
    std::string output_char = "▇";
    size_t width = DEFAULT_WIDTH;
    std::optional<size_t> height = std::nullopt;
    bool greyscale = false;
    Magick::FilterType filter_type = Magick::LanczosFilter;
};

const char USAGE[] =
    //TODO add filter arge
    R"(Img Print.
    Usage:
      img-print [-g] [-f <filtertype>] <filename>
      img-print [-g] [-f <filtertype>] <filename> <output-width>
      img-print [-g] [-f <filtertype>] <filename> <output-width> <output-height>
      img-print [-g] [-f <filtertype>] <filename> <output-width> <output-height> <output-character>
      img-print [-g] [-f <filtertype>]
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

inline std::variant<Arguments, std::string> get_args(int argc, char **argv)
{

    size_t arg_position =1;
    try
    {
        Arguments args;
        auto args_map = get_args_map(argc, argv);
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
        if (args_map["<output-character>"]) { args.output_char = args_map["<output-character>"].asString(); }
        return std::variant<Arguments, std::string>(args);
    } catch (const std::invalid_argument& e)
    {
        return fmt::format("Error: invalid argument \"\x1b[38;2;225;100;40m{}\x1b[0m\"", argv[arg_position]);
    }
}
#endif
