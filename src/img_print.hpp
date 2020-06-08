#ifndef IMGPRINT_HPP
#define IMGPRINT_HPP

#include <fmt/format.h>

#include <algorithm>
#include <fmt/format.h>
#include <cstdint>
#include <map>
#include <array>
#include <docopt/docopt.h>
#include <iostream>
#include <optional>
#include "cliargs.hpp"
#include "img_util.hpp"
std::string format_char_rgb(std::array<uint8_t, 4> pixel, const std::string_view c, const uint8_t opacity_cutoff = 30);
void image_print(const Arguments &args);


#endif
