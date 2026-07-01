#include "catch.hpp"
#include "../dicerollduel.hpp"

TEST_CASE("Dice Roll Duel bounds and logic", "[dicerollduel]") {
    dicerollduel game("TestPlayer", 100.0); 

    SECTION("Game name is correct") {
        REQUIRE(game.getName() == "Dice Roll Duel");
    }

    SECTION("Dice rolls are strictly within 1-6 range") {
        // rolldice() is public, so we can test the random generation
        for(int i = 0; i < 50; i++) {
            int roll = game.rolldice(); 
            REQUIRE(roll >= 1);
            REQUIRE(roll <= 6);
        }
    }
}