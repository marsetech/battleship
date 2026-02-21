#include "utils/GameUtils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("parseTerminalSize returns cols when valid") {
    REQUIRE(parseTerminalSize(24, 80) == 80);
    REQUIRE(parseTerminalSize(40, 120) == 120);
}

TEST_CASE("parseTerminalSize falls back to 80 on invalid input") {
    REQUIRE(parseTerminalSize(0, 0) == 80);
    REQUIRE(parseTerminalSize(-1, 100) == 80);
    REQUIRE(parseTerminalSize(24, -1) == 80);
}
