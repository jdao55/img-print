#include "img_util.hpp"

constexpr auto OUTPUT_COLOR_DEPTH = 255;
std::array<uint8_t, 4> get_pixel_rgba(const Magick::Quantum *pixels)
{
    auto red = uint8_t(pixels[0] / QuantumRange * OUTPUT_COLOR_DEPTH);
    auto green = uint8_t(pixels[1] / QuantumRange * OUTPUT_COLOR_DEPTH);
    auto blue = uint8_t(pixels[2] / QuantumRange * OUTPUT_COLOR_DEPTH);
    auto opacity = uint8_t(pixels[3] / QuantumRange * OUTPUT_COLOR_DEPTH);
    return std::array<uint8_t, 4>{ red, green, blue, opacity };
}

std::array<uint8_t, 4> get_pixel_ga(const Magick::Quantum *pixels)
{
    auto i = uint8_t(pixels[0] / QuantumRange * OUTPUT_COLOR_DEPTH);
    auto opacity = uint8_t(pixels[1] / QuantumRange * OUTPUT_COLOR_DEPTH);
    return std::array<uint8_t, 4>{ i, i, i, opacity };
}

void transform_image(Magick::Image &image, const size_t x, std::optional<size_t> y, const bool grayscale, const float text_ratio)
{
    if (!y.has_value())
    {
        auto img_dim = image.size();
        float ratio = static_cast<float>(img_dim.height()) / static_cast<float>(img_dim.width()) / text_ratio;
        y.emplace(static_cast<size_t>(static_cast<float>(x) * ratio));
    }
    Magick::Geometry scale(x, y.value());
    scale.aspect(true);
    image.scale(scale);
    if (grayscale)
    {
        image.type(MagickCore::GrayscaleAlphaType);
    }
    else
    {
        image.type(MagickCore::TrueColorAlphaType);
    }
}
