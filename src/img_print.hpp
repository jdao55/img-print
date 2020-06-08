#ifndef IMGPRINT_HPP
#define IMGPRINT_HPP

#include <fmt/format.h>

#include <vector>
#include <string>
#include <string_view>
#include "cliargs.hpp"
#include "img_util.hpp"

std::string format_char_rgba(double * pixel, std::string_view c, const uint8_t opacity_cutoff = 30);
std::string format_char_rgb(double* pixel, std::string_view c);
void image_print(const Arguments &args);


#endif
