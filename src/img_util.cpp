#include "img_util.hpp"

// constexpr auto OUTPUT_COLOR_DEPTH = 255;
// //converts quatum value to 0-255 value
// uint8_t quantum_to_uint8(const Magick::Quantum q)
// {
//     auto ratio =  std::min(1.0F,std::fabs(q) / QuantumRange);
//     return uint8_t(255*ratio);
// }

// std::array<uint8_t, 4> get_pixel_rgba(const Magick::Quantum *pixels)
// {
//     auto red = quantum_to_uint8(pixels[0]);
//     auto green = quantum_to_uint8(pixels[1]);
//     auto blue = quantum_to_uint8(pixels[2]);
//     auto opacity = quantum_to_uint8(pixels[3]);
//     return std::array<uint8_t, 4>{ red, green, blue, opacity };
// }

// std::array<uint8_t, 4> get_pixel_ga(const Magick::Quantum *pixels)
// {
//     auto i =  quantum_to_uint8(pixels[0]);
//     auto opacity = quantum_to_uint8(pixels[1]);
//     return std::array<uint8_t, 4>{ i, i, i, opacity };
// }

// void transform_image(Magick::Image &image, const Arguments& args, const float text_ratio)
// {
//     size_t y_val = 0;
//     if (!args.height.has_value())
//     {
//         auto img_dim = image.size();
//         float ratio = static_cast<float>(img_dim.height()) / static_cast<float>(img_dim.width()) / text_ratio;
//         y_val = static_cast<size_t>(static_cast<float>(args.width) * ratio);
//     }
//     else
//     {
//         y_val = args.height.value();
//     }
//     Magick::Geometry scale(args.width, y_val);
//     scale.aspect(true);
//     image.filterType(args.filter_type);
//     image.resize(scale);
//     image.write( "test.png" );
//     if (args.greyscale)
//     {
//         image.type(MagickCore::GrayscaleAlphaType);
//     }
//     else
//     {
//         image.type(MagickCore::TrueColorAlphaType);
//     }
// }
