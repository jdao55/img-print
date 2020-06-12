#ifndef IMGPRINT_HPP
#define IMGPRINT_HPP

#include <vector>
#include <string>
#include <string_view>
#include "cliargs.hpp"
#include "img_util.hpp"

[[nodiscard]] std::string
    format_char_rgba(uint8_t *pixel, std::string_view c, const uint8_t opacity_cutoff = 30);

[[nodiscard]] std::string format_char_rgb(uint8_t *pixel, std::string_view c);

[[nodiscard]] std::string format_char_g(uint8_t *pixel, std::string_view c);

[[nodiscard]] std::string
    format_char_ga(uint8_t *pixel, std::string_view c, const uint8_t opacity_cutoff = 30);

void print_rgba(uint8_t *pixels, const int height, const int width, std::string_view c);
void print_rgb(uint8_t * pixels, const int height,const int width, std::string_view c);
void print_ga(uint8_t *pixels, const int height, const int width, std::string_view c);
void print_g(uint8_t * pixels, const int height,const int width, std::string_view c);
void image_print(const Arguments &args);


#endif
