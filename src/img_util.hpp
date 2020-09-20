#ifndef IMG_UTIL_H
#define IMG_UTIL_H

#include <array>
#include <string>
#include <optional>


constexpr uint32_t rgb_to_hex(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t res = r << 8;
    res = (res + g) << 8;
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


void format_char_rgba(const uint8_t *pixel,
    const std::string_view c,
    const uint8_t opacity_cutoff = 30);

void format_char_rgb(const uint8_t *pixel, const std::string_view c);

void format_char_g(const uint8_t *pixel, const std::string_view c);

void format_char_ga(const uint8_t *pixel,
    const std::string_view c,
    const uint8_t opacity_cutoff = 30);

template<typename T>
constexpr bool contains(const auto &array, const T &key)
{
    return std::end(array) != std::find(std::begin(array), std::end(array), key);
}

#endif
