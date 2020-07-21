#ifndef IMG_UTIL_H
#define IMG_UTIL_H

#include <array>
#include <string>
#include <optional>

constexpr double get_wscale(const auto start_size, const auto target_size)
{
    return double(target_size) / double(start_size);
}

constexpr size_t reserve_size(const size_t h, const size_t w) { return (h + 1) * w * 24 + 7; }

inline double
    get_vscale(const std::optional<size_t> &in, const size_t image_y, const double w_scale)
{
    if (in.has_value())
    {
        return double(in.value()) / double(image_y);
    }
    return w_scale / 2.1;
}


[[nodiscard]] std::string format_char_rgba(const uint8_t *pixel,
    const std::string_view c,
    const uint8_t opacity_cutoff = 30);

[[nodiscard]] std::string format_char_rgb(const uint8_t *pixel, const std::string_view c);

[[nodiscard]] std::string format_char_g(const uint8_t *pixel, const std::string_view c);

[[nodiscard]] std::string format_char_ga(const uint8_t *pixel,
    const std::string_view c,
    const uint8_t opacity_cutoff = 30);

template<typename T>
constexpr bool contains(const auto &array, const T &key)
{
    return std::end(array) != std::find(std::begin(array), std::end(array), key);
}

#endif
