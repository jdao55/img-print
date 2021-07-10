#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <img_print.hpp>
#include <img_util.hpp>
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

TEST_CASE("rgb_to_hex", "util")
{
    REQUIRE(rgb_to_hex(0x18, 0x21, 0xFF) == 0x1821FF);
    REQUIRE(rgb_to_hex(0xFF, 0xFF, 0x00) == 0xFFFF00);
    REQUIRE(rgb_to_hex(0x12, 0x61, 0x3F) == 0x12613f);
    REQUIRE(rgb_to_hex(0x18, 0x21, 0xFF) == 0x1821FF);
}
