#ifndef IMG_UTIL_H
#define IMG_UTIL_H

#include <array>
#include <string>
#include <optional>

constexpr double get_wscale(int start_size, int target_size)
{
    return double(target_size) / double(start_size);
}

inline double get_vscale(std::optional<size_t> in, const int image_y, const double w_scale)
{
    if (in.has_value())
    {
        return double(in.value()) / double(image_y);
    }
    return w_scale / 2.1;
}


[[nodiscard]] std::string
format_char_rgba(uint8_t *pixel, std::string_view c, const uint8_t opacity_cutoff = 30);

[[nodiscard]] std::string format_char_rgb(uint8_t *pixel, std::string_view c);

[[nodiscard]] std::string format_char_g(uint8_t *pixel, std::string_view c);

[[nodiscard]] std::string
format_char_ga(uint8_t *pixel, std::string_view c, const uint8_t opacity_cutoff = 30);

template <typename T>
constexpr bool contains(const auto& array, const T& key)
{
    for(const auto& element: array)
    {
        if(key==element)
        {
            return true;
        }
    }
    return false;
}

#endif
