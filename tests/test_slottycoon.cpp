#include "catch.hpp"
#include <cmath>
#include "../SlotTycoon.hpp"

TEST_CASE("Slot Tycoon mechanics and math", "[slottycoon]") {
    SlotTycoon game("TestPlayer", 1000.0);

    SECTION("Base Level 1 probabilities and multipliers") {
        // Level 1: 0.2 + (1 * 0.05) = 0.25
        REQUIRE(std::abs(game.getWinProbability() - 0.25) < 0.001);
        // Level 1: 2.0 + (1 * 0.5) = 2.5
        REQUIRE(std::abs(game.getPayoutMultiplier() - 2.5) < 0.001);
    }
    
    SECTION("Successful Machine Upgrade logic") {
        double balance = 1000.0;
        game.upgradeMachine(balance); // Cost at Level 1 is $300
        
        REQUIRE(balance == 700.0);
        // Upgraded to Level 2: 0.2 + (2 * 0.05) = 0.30
        REQUIRE(std::abs(game.getWinProbability() - 0.30) < 0.001);
        // Upgraded to Level 2: 2.0 + (2 * 0.5) = 3.0
        REQUIRE(std::abs(game.getPayoutMultiplier() - 3.0) < 0.001);
    }
    
    SECTION("Failed upgrade due to insufficient balance") {
        double balance = 200.0;
        game.upgradeMachine(balance); // Cost is $300, should fail
        
        REQUIRE(balance == 200.0); // Balance should remain untouched
        // Level should remain 1
        REQUIRE(std::abs(game.getWinProbability() - 0.25) < 0.001);
    }
}