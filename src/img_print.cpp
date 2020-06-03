#include "img_print.hpp"

std::string format_char_rgb(std::array<uint8_t, 4> pixel, std::string_view c, const uint8_t opacity_cutoff)
{
    if (pixel[3] > opacity_cutoff)
    {
        return fmt::format("\x1b[38;2;{};{};{}m{}", pixel[0], pixel[1], pixel[2], c);
    }
    return " ";
}


void image_print(const Arguments &args)
{
    Magick::Image image;
    // Read a file into image object
    image.read(args.filename);

    // resize image
    transform_image(image, args);
    Magick::Pixels view(image);

    const auto width = image.size().width();
    const auto height = image.size().height();
    const Magick::Quantum *pixels = view.getConst(0, 0, width, height);
    if (args.greyscale)
    {
        for (size_t row = 0; row < height; ++row)
        {
            for (size_t column = 0; column < width; ++column, pixels+=2)
            {
                auto pixel = get_pixel_ga(pixels);
                fmt::print(format_char_rgb(pixel, args.output_char));
            }
            fmt::print("\n");
        }
    }
    else
    {
        for (size_t row = 0; row < height; ++row)
        {
            for (size_t column = 0; column < width; ++column, pixels+=4)
            {
                auto pixel = get_pixel_rgba(pixels);
                fmt::print(format_char_rgb(pixel, args.output_char));
            }
            fmt::print("\n");
        }
    }
    fmt::print("\x1b[0m\n");
}
