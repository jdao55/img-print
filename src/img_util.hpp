#ifndef IMG_UTIL_H
#define IMG_UTIL_H

#include <array>
#include <bits/stdint-uintn.h>
#include <string>
#include <optional>
#include <vector>
#include <fmt/format.h>
#include <fmt/compile.h>
#include <fmt/color.h>

constexpr uint32_t rgb_to_hex(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t res = r << 8u;
    res = (res + g) << 8u;
    res = (res + b);
    return res;
}
constexpr double get_wscale(const auto start_size, const auto target_size)
{
    return double(target_size) / double(start_size);
}

inline double
    get_vscale(const std::optional<size_t> &in, const size_t image_y, const double w_scale)
{
    if (in.has_value())
    {
        return double(in.value()) / double(image_y);
    }
    return w_scale / 2.1;
}
constexpr auto fmt_colour(uint8_t r, uint8_t g, uint8_t b)
{
    const auto hexcolor = rgb_to_hex(r, g, b);
    return fmt::fg(fmt::detail::color_type(hexcolor));
}

void format_char_rgba(auto pixel, std::string_view c, const uint8_t opacity_cutoff = 30)
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

void format_char_rgb(auto pixel, std::string_view c)
{
    fmt::print(fmt_colour(pixel[0], pixel[1], pixel[2]), FMT_COMPILE_H_("{}"), c);
}

void format_char_g(auto pixel, std::string_view c)
{
    const auto avg = static_cast<uint8_t>((pixel[0] + pixel[1] + pixel[2]) / 3);
    fmt::print(fmt_colour(avg, avg, avg), FMT_COMPILE_H_("{}"), c);
}

void format_char_ga(auto pixel, std::string_view c, const uint8_t opacity_cutoff = 30)
{

    if (*(pixel + 3) > opacity_cutoff)
    {
        const auto avg = static_cast<uint8_t>((pixel[0] + pixel[1] + pixel[2]) / 3);
        fmt::print(fmt_colour(avg, avg, avg), FMT_COMPILE_H_("{}"), c);
    }
    else
    {
        fmt::print(FMT_COMPILE_H_(" "));
    }
}


template<typename T>
constexpr bool contains(const auto &array, const T &key)
{
    return std::end(array) != std::find(std::begin(array), std::end(array), key);
}


[[nodiscard]] constexpr bool check_buffer_size(auto h, auto w, auto n, bool has_aplha)
{
    auto expected = has_aplha ? h * w * 4 : h * w * 3;
    return expected == n;
}

#endif
