#include "img_print.hpp"
#include <vips/vips8>
#include <optional>


void print(const uint8_t *pixels,
    const size_t height,
    const size_t width,
    const std::string_view c,
    bool has_alpha,
    bool greyscale)
{
    if (greyscale)
    {
        if (has_alpha)
        {
            print_ga(pixels, height, width, c);
        }
        else
        {
            print_g(pixels, height, width, c);
        }
    }
    else
    {
        if (has_alpha)
        {
            print_rgba(pixels, height, width, c);
        }
        else
        {
            print_rgb(pixels, height, width, c);
        }
    }
}
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

[[nodiscard]] constexpr bool check_buffer_size(auto h, auto w, auto n, bool has_aplha)
{
    auto expected = has_aplha ? h * w * 4 : h * w * 3;
    return expected == n;
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
    if (!check_buffer_size(out.height(), out.width(), n, out.has_alpha()))
    {
        fmt::print("error reading image");
    }
    else
    {
        print(pixels, out.height(), out.width(), args.output_char, out.has_alpha(), args.greyscale);
    }

    g_free(pixels);
    vips_shutdown();
}
