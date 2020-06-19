#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../src/img_print.hpp"
#include "../src/img_util.hpp"
#include <array>

using pixel_t = std::array<uint8_t, 4>;
constexpr double epsilon = 0.001;

constexpr double rel_error(double calc_val, double act_val)
{
    return (calc_val - act_val) / (act_val);
}

TEST_CASE("get_wscale", "[util]")
{
    REQUIRE(rel_error(get_wscale(1, 0), 0.1) < epsilon);
    REQUIRE(rel_error(get_wscale(1, 1), 1.0) < epsilon);
    REQUIRE(rel_error(get_wscale(4, 2), 0.5) < epsilon);
    REQUIRE(rel_error(get_wscale(1000, 80), 0.08) < epsilon);
    REQUIRE(rel_error(get_wscale(4096, 64), 0.015625) < epsilon);
}

TEST_CASE("get_vscale", "[util]")
{
    std::optional<size_t> empty = std::nullopt;
    std::optional<size_t> y1 = 30;
    std::optional<size_t> y2 = 50;
    REQUIRE(rel_error(get_vscale(empty, 500, 2.1), 1.0) < epsilon);
    REQUIRE(rel_error(get_vscale(empty, 2160, 0.125), 0.0595238) < epsilon);
    REQUIRE(rel_error(get_vscale(y1, 300, 0.1), 0.1) < epsilon);
    REQUIRE(rel_error(get_vscale(y2, 4000, 0.32), 0.0125) < epsilon);
}
TEST_CASE("Test char print", "[]")
{

    SECTION("rgba")
    {
        uint8_t a1[4] = { 255, 255, 255, 255 };
        uint8_t a2[4] = { 255, 255, 255, 0 };
        uint8_t a3[4] = { 50, 50, 55, 255 };
        uint8_t a4[4] = { 25, 255, 55, 0 };
        REQUIRE_THAT(format_char_rgba(a1, "#"), Catch::Equals("\x1b[38;2;255;255;255m#"));
        REQUIRE_THAT(format_char_rgba(a2, "#"), Catch::Equals(" "));
        REQUIRE_THAT(format_char_rgba(a3, "#"), Catch::Equals("\x1b[38;2;50;50;55m#"));
        REQUIRE_THAT(format_char_rgba(a4, "#"), Catch::Equals(" "));
    }
    SECTION("rbg")
    {
        uint8_t a1[3] = { 255, 255, 255 };
        uint8_t a2[3] = { 0, 0, 0 };
        uint8_t a3[3] = { 128, 128, 128 };
        uint8_t a4[3] = { 0, 255, 22 };
        REQUIRE_THAT(format_char_rgb(a1, "#"), Catch::Equals("\x1b[38;2;255;255;255m#"));
        REQUIRE_THAT(format_char_rgb(a2, "#"), Catch::Equals("\x1b[38;2;0;0;0m#"));
        REQUIRE_THAT(format_char_rgb(a3, "#"), Catch::Equals("\x1b[38;2;128;128;128m#"));
        REQUIRE_THAT(format_char_rgb(a4, "#"), Catch::Equals("\x1b[38;2;0;255;22m#"));
    }
    SECTION("grey")
    {
        uint8_t a1[3] = { 255, 255, 255 };
        uint8_t a2[3] = { 192, 0, 0 };
        uint8_t a3[3] = { 128, 128, 60 };
        REQUIRE_THAT(format_char_g(a1, "#"), Catch::Equals("\x1b[38;2;255;255;255m#"));
        REQUIRE_THAT(format_char_g(a2, "#"), Catch::Equals("\x1b[38;2;64;64;64m#"));
        REQUIRE_THAT(format_char_g(a3, "#"), Catch::Equals("\x1b[38;2;105;105;105m#"));
    }
    SECTION("grey-hap")
    {
        uint8_t a1[4] = { 255, 255, 255, 255 };
        uint8_t a2[4] = { 192, 0, 0, 255 };
        uint8_t a3[4] = { 128, 128, 60, 130 };
        uint8_t a4[4] = { 0, 255, 22, 0 };
        REQUIRE_THAT(format_char_ga(a1, "#"), Catch::Equals("\x1b[38;2;255;255;255m#"));
        REQUIRE_THAT(format_char_ga(a2, "#"), Catch::Equals("\x1b[38;2;64;64;64m#"));
        REQUIRE_THAT(format_char_ga(a3, "#"), Catch::Equals("\x1b[38;2;105;105;105m#"));
        REQUIRE_THAT(format_char_ga(a4, "#"), Catch::Equals(" "));
    }
}
