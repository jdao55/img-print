#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <Magick++.h>
#include "../img_print.hpp"
#include <array>

using pixel_t = std::array<uint8_t, 4>;

TEST_CASE("Test char print", "[]")
{

    SECTION("formatting chars")
    {
        REQUIRE_THAT(format_char_rgb(pixel_t{ 255, 255, 255, 255 }, "#"), Catch::Equals("\x1b[38;2;255;255;255m#"));
        REQUIRE_THAT(format_char_rgb(pixel_t{ 255, 255, 255, 0 }, "#"), Catch::Equals(" "));
        REQUIRE_THAT(format_char_rgb(pixel_t{ 50, 50, 55, 31 }, "#"), Catch::Equals("\x1b[38;2;50;50;55m#"));
        REQUIRE_THAT(format_char_rgb(pixel_t{ 50, 50, 55, 30 }, "#"), Catch::Equals(" "));
    }
    SECTION("Unicode")
    {
        REQUIRE_THAT(format_char_rgb(pixel_t{ 255, 255, 255, 255 }, "▇"), Catch::Equals("\x1b[38;2;255;255;255m▇"));
        REQUIRE_THAT(format_char_rgb(pixel_t{ 255, 255, 255, 0 }, "▇"), Catch::Equals(" "));
        REQUIRE_THAT(format_char_rgb(pixel_t{ 50, 50, 55, 31 }, "▇"), Catch::Equals("\x1b[38;2;50;50;55m▇"));
        REQUIRE_THAT(format_char_rgb(pixel_t{ 50, 50, 55, 30 }, "▇"), Catch::Equals(" "));
    }
}
