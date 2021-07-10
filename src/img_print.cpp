#include <img_print.hpp>
#include <vips/vips8>
#include <optional>

void print(const std::vector<uint8_t> &pixels,
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
            print_g<ColorChannel::rgba>(pixels, height, width, c);
        }
        else
        {
            print_g<ColorChannel::rgb>(pixels, height, width, c);
        }
    }
    else
    {
        if (has_alpha)
        {
            print_rgb<ColorChannel::rgba>(pixels, height, width, c);
        }
        else
        {
            print_rgb<ColorChannel::rgb>(pixels, height, width, c);
        }
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

    size_t n = 0;
    auto *pixels_ptr = static_cast<uint8_t *>(out.write_to_memory(&n));
    auto pixels = std::vector<uint8_t>(pixels_ptr, pixels_ptr + n);
    if (!check_buffer_size(out.height(), out.width(), n, out.has_alpha()))
    {
        fmt::print("error reading image");
    }
    else
    {
        print(pixels, out.height(), out.width(), args.output_char, out.has_alpha(), args.greyscale);
    }

    g_free(pixels_ptr);
    vips_shutdown();
}
