#include "img_util.hpp"
#include <fmt/format.h>
#include <fmt/compile.h>
#include <fmt/color.h>


constexpr auto fmt_colour(uint8_t r, uint8_t g, uint8_t b)
{
    const auto hexcolor = rgb_to_hex(r, g, b);
    return fmt::fg(fmt::detail::color_type(hexcolor));
}


void format_char_rgba(const uint8_t *pixel, const std::string_view c, const uint8_t opacity_cutoff)
{
    if (pixel[3] > opacity_cutoff)
    {
        fmt::print(fmt_colour(pixel[0], pixel[1], pixel[2]), FMT_COMPILE_H_("{}"), c);
    }
    else
    {
        fmt::print(FMT_COMPILE_H_(" "));
    }
}

void format_char_rgb(const uint8_t *pixel, const std::string_view c)
{
    fmt::print(fmt_colour(pixel[0], pixel[1], pixel[2]), FMT_COMPILE_H_("{}"), c);
}

void format_char_g(const uint8_t *pixel, const std::string_view c)
{
    const uint8_t avg = static_cast<uint8_t>((pixel[0] + pixel[1] + pixel[2]) / 3);
    fmt::print(fmt_colour(pixel[0], pixel[0], pixel[0]), FMT_COMPILE_H_("{}"), c);
}

void format_char_ga(const uint8_t *pixel, const std::string_view c, const uint8_t opacity_cutoff)
{

    if (pixel[3] > opacity_cutoff)
    {
        const uint8_t avg = static_cast<uint8_t>((pixel[0] + pixel[1] + pixel[2]) / 3);
        fmt::print(fmt_colour(pixel[0], pixel[0], pixel[0]), FMT_COMPILE_H_("{}"), c);
    }
    else
    {
        fmt::print(FMT_COMPILE_H_(" "));
    }
}
