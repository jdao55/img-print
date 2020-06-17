#ifndef IMGPRINT_HPP
#define IMGPRINT_HPP

#include "cliargs.hpp"
#include "img_util.hpp"

void print_rgba(uint8_t *pixels, const int height, const int width, std::string_view c);
void print_rgb(uint8_t * pixels, const int height,const int width, std::string_view c);
void print_ga(uint8_t *pixels, const int height, const int width, std::string_view c);
void print_g(uint8_t * pixels, const int height,const int width, std::string_view c);
void image_print(const Arguments &args);


#endif
