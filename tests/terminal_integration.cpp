#include "utils/GameUtils.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("getTerminal always returns positive width") {
    int width = getTerminal();

		REQUIRE(width > 0);
    REQUIRE(width <= 500);
}
