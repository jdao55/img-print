#ifndef IMGPRINT_HPP
#define IMGPRINT_HPP

#include "cliargs.hpp"
#include "img_util.hpp"

std::string print_rgba(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c);
std::string print_rgb(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c);
std::string print_ga(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c);
std::string print_g(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c);
void image_print(const Arguments &args);


#endif
