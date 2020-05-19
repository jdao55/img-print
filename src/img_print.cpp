#include "img_print.hpp"

constexpr auto OUTPUT_COLOR_DEPTH = 255;

std::string format_char_rgb(std::array<uint8_t, 4> pixel, std::string_view c, const uint8_t opacity_cutoff)
{
    if (pixel[3] > opacity_cutoff)
    {
        return fmt::format("\x1b[38;2;{};{};{}m{}", pixel[0], pixel[1], pixel[2], c);
    }
    return " ";
}

//converts quatum value to 0-255 value
uint8_t quantum_to_uint8(const Magick::Quantum q)
{
    auto ratio =  std::min(1.0F, q / QuantumRange);
    return uint8_t(255*ratio);
}

std::array<uint8_t, 4> get_pixel_rgba(const Magick::Quantum *pixels)
{
    auto red = quantum_to_uint8(pixels[0]);
    auto green = quantum_to_uint8(pixels[1]);
    auto blue = quantum_to_uint8(pixels[2]);
    auto opacity = quantum_to_uint8(pixels[3]);
    return std::array<uint8_t, 4>{ red, green, blue, opacity };
}

std::array<uint8_t, 4> get_pixel_ga(const Magick::Quantum *pixels)
{
    auto i = uint8_t(pixels[0] / QuantumRange * OUTPUT_COLOR_DEPTH);
    auto opacity = uint8_t(pixels[1] / QuantumRange * OUTPUT_COLOR_DEPTH);
    return std::array<uint8_t, 4>{ i, i, i, opacity };
}

void transform_image(Magick::Image &image, const Arguments& args, const float text_ratio)
{
    size_t y_val = 0;
    if (!args.height.has_value())
    {
        auto img_dim = image.size();
        float ratio = static_cast<float>(img_dim.height()) / static_cast<float>(img_dim.width()) / text_ratio;
        y_val = static_cast<size_t>(static_cast<float>(args.width) * ratio);
    }
    else
    {
        y_val = args.height.value();
    }
    Magick::Geometry scale(args.width, y_val);
    scale.aspect(true);
    image.filterType(args.filter_type);
    image.resize(scale);
    if (args.greyscale)
    {
        image.type(MagickCore::GrayscaleAlphaType);
    }
    else
    {
        image.type(MagickCore::TrueColorAlphaType);
    }
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
