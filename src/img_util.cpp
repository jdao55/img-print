#include "img_util.hpp"
#include <fmt/format.h>

std::string format_char_rgba(uint8_t *pixel, std::string_view c, const uint8_t opacity_cutoff)
{
    if (pixel[3] > opacity_cutoff)
    {
        return fmt::format("\x1b[38;2;{};{};{}m{}", pixel[0], pixel[1], pixel[2], c);
    }
    return " ";
}
std::string format_char_rgb(uint8_t *pixel, std::string_view c)
{
    return fmt::format("\x1b[38;2;{};{};{}m{}", pixel[0], pixel[1], pixel[2], c);
}
std::string format_char_g(uint8_t *pixel, std::string_view c)
{
    uint8_t avg = static_cast<uint8_t>((pixel[0] + pixel[1] + pixel[2]) / 3);
    return fmt::format("\x1b[38;2;{0};{0};{0}m{1}", avg, c);
}

std::string format_char_ga(uint8_t *pixel, std::string_view c, const uint8_t opacity_cutoff)
{
    uint8_t avg = static_cast<uint8_t>((pixel[0] + pixel[1] + pixel[2]) / 3);
    if (pixel[3] > opacity_cutoff)
    {
        return fmt::format("\x1b[38;2;{0};{0};{0}m{1}", avg, c);
    }
    return " ";
}
