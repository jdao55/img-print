#include "img_print.hpp"



void print_char_rgb(std::array<uint8_t,4> pixel, std::string_view c)
{
    if(pixel[3]> 30)
        fmt::print("\x1b[38;2;{};{};{}m{}", pixel[0], pixel[1], pixel[2], c);
    else
        fmt::print(" ");
}


std::array<uint8_t, 4> get_pixel_rgba(const Magick::Quantum *&pixels)
{
    const uint32_t max_color_val = 255;
    uint8_t red = uint8_t(std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255),   max_color_val));
    uint8_t green =uint8_t(std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255),   max_color_val));
    uint8_t blue = uint8_t(std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255),   max_color_val));
    uint8_t opacity = uint8_t(std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255),   max_color_val));
    return std::array<uint8_t, 4>{red, green, blue, opacity};
}

std::array<uint8_t, 4> get_pixel_ga(const Magick::Quantum *&pixels)
{
    const uint32_t max_color_val = 255;
    uint8_t i = uint8_t(std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255),   max_color_val));
    uint8_t opacity = uint8_t(std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255),   max_color_val));
    return std::array<uint8_t, 4>{i, i, i, opacity};
}

void transform_image(Magick::Image &image, const size_t x, const size_t y, const bool grayscale)
{
    Magick::Geometry scale(x, y);
    scale.aspect(true);
    image.scale(scale);
    if(grayscale)
        image.type(MagickCore::GrayscaleAlphaType);
    else
        image.type(MagickCore::TrueColorAlphaType);
}
void image_print(const Arguments &args)
{
    Magick::Image image;
    // Read a file into image object
    image.read(args.filename);

    transform_image(image, args.width, args.height, args.greyscale);

    Magick::Pixels view(image);

    const Magick::Quantum *pixels = view.getConst(0, 0, args.width, args.height);
    if(args.greyscale)
    {
        for (size_t row = 0; row < args.height; ++row)
        {
            for (size_t column = 0; column < args.width; ++column)
            {
                auto pixel = get_pixel_ga(pixels);
                print_char_rgb(pixel, args.output_char);
            }
            fmt::print("\n");
        }
    }
    else {
        for (size_t row = 0; row < args.height; ++row)
        {
            for (size_t column = 0; column < args.width; ++column)
            {
                auto pixel = get_pixel_rgba(pixels);
                print_char_rgb(pixel, args.output_char);
            }
            fmt::print("\n");
        }
    }
    fmt::print("\x1b[0m\n");

}
