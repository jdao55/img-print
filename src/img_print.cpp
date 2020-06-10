#include "img_print.hpp"
#include <vips/vips8>
#include <iostream>
#include <algorithm>
#include <optional>


constexpr double get_wscale(int start_size, int target_size)
{
    return double(target_size) / double(start_size);
}

double get_vscale(std::optional<size_t> in, const int image_y, const double w_scale)
{
    if (in.has_value())
    {
        return double(in.value()) / double(image_y);
    }
    return w_scale / 2.1;
}

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


void image_print(const Arguments &args)
{
    using namespace vips;
    if (VIPS_INIT("img-print"))
        vips_error_exit(NULL);

    VImage in = vips::VImage::new_from_file(
        args.filename.c_str(), vips::VImage::option()->set("access", "sequential"));

    auto height = in.height();
    auto width = in.width();


    auto w_scale = get_wscale(width, args.width);
    auto v_scale = get_vscale(args.height, height, w_scale);
    VImage out = in.resize(
        w_scale, VImage::option()->set("kernel", args.filter_type.c_str())->set("vscale", v_scale));

    size_t n;
    auto pixels = reinterpret_cast<uint8_t *>(out.write_to_memory(&n));
    uint8_t *data_iter = pixels;
    for (auto y = 0; y < out.height(); ++y)
    {
        for (auto x = 0; x < out.width(); ++x)
        {
            if (out.has_alpha())
            {
                fmt::print(format_char_rgba(data_iter, args.output_char));
                data_iter += 4;
            }
            else
            {
                fmt::print(format_char_rgb(data_iter, args.output_char));
                data_iter += 3;
            }
        }
        fmt::print("\n");
    }
    fmt::print("\x1b[0m\n");
    g_free(pixels);
    vips_shutdown();
}
