#include "img_print.hpp"
#include <vips/vips8>
#include <optional>

void print_rgba(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c)
{

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            format_char_rgba(pixels, c);
            pixels += 4;
        }
        fmt::print("\n");
    }
}

void print_rgb(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c)
{

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            format_char_rgb(pixels, c);
            pixels += 3;
        }
        fmt::print("\n");
    }
}


void print_ga(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c)
{

    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            format_char_ga(pixels, c);
            pixels += 4;
        }
        fmt::print("\n");
    }

}


void print_g(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c)
{
    std::string ret;
    ret.reserve(reserve_size(height, width));
    for (size_t y = 0; y < height; ++y)
    {
        for (size_t x = 0; x < width; ++x)
        {
            format_char_g(pixels, c);
            pixels += 3;
        }
        fmt::print("\n");
    }

}


void image_print(const Arguments &args)
{
    using namespace vips;
    if (VIPS_INIT("img-print"))
        vips_error_exit(NULL);

    VImage in = vips::VImage::new_from_file(
        args.filename.c_str(), vips::VImage::option()->set("access", "sequential"));

    const size_t height = in.height();
    const size_t width = in.width();


    const auto w_scale = get_wscale(width, args.width);
    const auto v_scale = get_vscale(args.height, height, w_scale);
    VImage out = in.resize(
        w_scale, VImage::option()->set("kernel", args.filter_type.c_str())->set("vscale", v_scale));

    size_t n;
    auto pixels = reinterpret_cast<uint8_t *>(out.write_to_memory(&n));
    if (args.greyscale)
    {
        if (out.has_alpha())
        {
            print_ga(pixels, out.height(), out.width(), args.output_char);
        }
        else
        {
            print_g(pixels, out.height(), out.width(), args.output_char);
        }
    }
    else
    {
        if (out.has_alpha())
        {
            print_rgba(pixels, out.height(), out.width(), args.output_char);
        }
        else
        {
            print_rgb(pixels, out.height(), out.width(), args.output_char);
        }
    }
    g_free(pixels);
    vips_shutdown();
}
