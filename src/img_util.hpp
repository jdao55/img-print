#ifndef IMG_UTIL_H
#define IMG_UTIL_H
#include <fmt/format.h>
#include <Magick++.h>
#include <MagickCore/image.h>
#include <algorithm>
#include <fmt/format.h>
#include <map>
#include <array>
#include <docopt/docopt.h>
#include <optional>
#include "cliargs.hpp"

std::array<uint8_t, 4> get_pixel_rgba(const Magick::Quantum *pixels);
std::array<uint8_t, 4> get_pixel_ga(const Magick::Quantum *pixels);
void transform_image(Magick::Image &image,
    const size_t x,
    std::optional<size_t> y,
    const bool grayscale,
    const float text_ratio = 2.1F);
#endif
