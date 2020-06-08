#include "img_print.hpp"
#include <vips/vips8>
#include <iostream>
#include <algorithm>

uint8_t to_uint8_t(const double n)
{
    auto n_abs = std::fabs(n);
    return std::min(uint8_t(255), uint8_t(n_abs));
}


constexpr double get_scale(size_t start_size, size_t target_size)
{
    return double(target_size)/ double (start_size);
}

// std::string format_char_rgba(std::vector<double> pixel, std::string_view c, const uint8_t opacity_cutoff)
// {
//     if (pixel[3] > opacity_cutoff)
//     {
//         return fmt::format("\x1b[38;2;{};{};{}m{}",
//                        to_uint8_t(pixel[0]),
//                        to_uint8_t(pixel[1]),
//                        to_uint8_t(pixel[2]),
//                        c);
//     }
//     return " ";
// }
// std::string format_char_rgb(std::vector<double> pixel, std::string_view c)
// {
//     return fmt::format("\x1b[38;2;{};{};{}m{}",
//                        to_uint8_t(pixel[0]),
//                        to_uint8_t(pixel[1]),
//                        to_uint8_t(pixel[2]),
//                        c);
// }

std::string format_char_rgba(double* pixel, std::string_view c, const uint8_t opacity_cutoff)
{
    if (pixel[3] > opacity_cutoff)
    {
        return fmt::format("\x1b[38;2;{};{};{}m{}",
                       to_uint8_t(pixel[0]),
                       to_uint8_t(pixel[1]),
                       to_uint8_t(pixel[2]),
                       c);
    }
    return " ";
}
std::string format_char_rgb(double* pixel, std::string_view c)
{
    return fmt::format("\x1b[38;2;{};{};{}m{}",
                       to_uint8_t(pixel[0]),
                       to_uint8_t(pixel[1]),
                       to_uint8_t(pixel[2]),
                       c);
}




void image_print(const Arguments &args)
{
    using namespace vips;
    if( VIPS_INIT( "img-print" ) )
		vips_error_exit( NULL );

    VImage in = vips::VImage::new_from_file( args.filename.c_str(), vips::VImage::option()
		->set( "access", "sequential" ) );

    //auto height = in.height();
    auto width = in.width();

    auto w_scale =get_scale(width, args.width);
    VImage out = in.resize(w_scale, VImage::option()
                           ->set("kernel", "lanczos3")
                           ->set("vscale", w_scale/2.0));

    VipsImage *out_ns;
    vips_image_decode(out, &out_ns);
    double * pixel_data;
    size_t n;
    //auto pixel_data = (double*)(out.data());
    out.write_to_buffer()
    auto data_iter = pixel_data;
    for(auto y = 0 ; y < out.height(); ++y)
    {
        for(auto x = 0; x <out.width(); ++x)
        {
            if(out.has_alpha())
            {
                fmt::print(format_char_rgba(data_iter, args.output_char));
                data_iter+=4;
            }
            else {
                fmt::print(format_char_rgb(data_iter, args.output_char));
                data_iter+=3;
            }
        }
        fmt::print("\n");
    }
}
