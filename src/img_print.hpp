#ifndef IMGPRINT_HPP
#define IMGPRINT_HPP

#include "cliargs.hpp"
#include "img_util.hpp"
#include <vector>


void image_print(const Arguments &args);

enum ColorChannel : int {
    rgb = 3,
    rgba = 4,
};

template<ColorChannel CC>
void print_rgb(const std::vector<uint8_t> &pixels_vec,
    const size_t height,
    const size_t width,
    const std::string_view c)
{
    auto pixels = pixels_vec.begin();
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            if constexpr (CC == ColorChannel::rgb)
            {
                format_char_rgb(pixels, c);
            }
            else
            {
                format_char_rgba(pixels, c);
            }
            pixels += CC;
        }
        fmt::print("\n");
    }
}

template<ColorChannel CC>
void print_g(const std::vector<uint8_t> &pixels_vec,
    const size_t height,
    const size_t width,
    const std::string_view c)
{
    auto pixels = pixels_vec.begin();
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            if constexpr (CC == ColorChannel::rgb)
            {
                format_char_g(pixels, c);
            }
            else
            {
                format_char_ga(pixels, c);
            }
            pixels += CC;
        }
        fmt::print("\n");
    }
}

#endif
