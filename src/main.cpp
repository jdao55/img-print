#include <Magick++.h>
#include <MagickCore/image.h>
#include <algorithm>
#include <fmt/format.h>
#include <cstdint>

void print_char_24( uint32_t r, uint32_t g, uint32_t b) { fmt::print("\x1b[38;2;{};{};{}m#", r, g, b); }

int main([[maybe_unused]] int argc, char **argv)
{
    Magick::InitializeMagick(*argv);

    Magick::Image image;
    try
    {
        // Read a file into image object
        image.read(argv[1]);
        image.type(MagickCore::TrueColorAlphaType);
        size_t width = 80;
        size_t height = 40;
        // Crop the image to specified size (width, height, xOffset, yOffset)
        Magick::Geometry scale(width, height);
        scale.aspect(true);
        image.resize(scale);
        image.write("test.png");

        Magick::Pixels view(image);

        const Magick::Quantum *pixels = view.getConst(0, 0, width, height);
        for (size_t row = 0; row < height; ++row)
        {
            for (size_t column = 0; column < width; ++column)
            {
                auto red = std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255), 255u);
                auto green = std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255), 255u);
                auto blue =  std::min(static_cast<uint32_t>(*pixels++ / QuantumRange * 255), 255u);
                auto opacity = *pixels++ / QuantumRange * 255;
                if (opacity > 30)
                {
                    print_char_24(red, green, blue);
                }
                else
                {
                    fmt::print(" ");
                }
            }
            fmt::print("\n");
        }
        fmt::print("\x1b[0m\n");
    } catch (std::exception &error_)
    {
        fmt::print("error\n");
        return 1;
    }
    return 0;
}
