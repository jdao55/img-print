#ifndef IMGPRINT_HPP
#define IMGPRINT_HPP

#include <cstdint>
#include <fmt/format.h>
#include <Magick++.h>
#include <MagickCore/image.h>
#include <algorithm>
#include <cstddef>
#include <fmt/format.h>
#include <cstdint>
#include <map>
#include <array>
#include <string_view>
#include <docopt/docopt.h>
#include <iostream>

#include "cliargs.hpp"

std::string format_char_rgb(std::array<uint8_t, 4> pixel, const std::string_view c);

std::array<uint8_t, 4> get_pixel_rgba(const Magick::Quantum *&pixels);
std::array<uint8_t, 4> get_pixel_ga(const Magick::Quantum *&pixels);
void transform_image(Magick::Image &image, const size_t x, const size_t y, const bool grayscale);

void image_print(const Arguments &args);


#endif
