#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <Magick++.h>
#include "../src/img_print.hpp"
#include "../src/img_util.hpp"
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

TEST_CASE("Tests for get pixel rgb function")
{
    Magick::Quantum const p_max[4] {65535, 65535, 65535, 65535};
    auto res_max = get_pixel_rgba(p_max);
    REQUIRE(res_max[0]==255);
    REQUIRE(res_max[1]==255);
    REQUIRE(res_max[2]==255);
    REQUIRE(res_max[3]==255);

    Magick::Quantum const p_mid[4] {32768, 0, 32768, 65535};
    auto res_mid = get_pixel_rgba(p_mid);
    REQUIRE(res_mid[0]==127);
    REQUIRE(res_mid[1]==0);
    REQUIRE(res_mid[2]==127);
    REQUIRE(res_mid[3]==255);
}
