#include "catch.hpp"
#include "../ThreeCardPoker.hpp"
#include <vector>

TEST_CASE("Three Card Poker hand evaluations", "[threecardpoker]") {
    double balance = 500.0;
    ThreeCardPoker game("TestPlayer", balance);

    SECTION("Three of a Kind (10x Payout)") {
        std::vector<int> hand = {7, 7, 7};
        REQUIRE(game.evaluateHand(hand) == 10);
    }

    SECTION("Straight (6x Payout)") {
        std::vector<int> hand = {4, 5, 6};
        REQUIRE(game.evaluateHand(hand) == 6);
    }

    SECTION("Pair + Near Sequence (4x Payout)") {
        std::vector<int> hand = {5, 5, 6};
        REQUIRE(game.evaluateHand(hand) == 4);
    }

    SECTION("Pair (2x Payout)") {
        std::vector<int> hand = {8, 8, 2};
        REQUIRE(game.evaluateHand(hand) == 2);
    }

    SECTION("High Card / Loss (0x Payout)") {
        std::vector<int> hand = {2, 7, 10};
        REQUIRE(game.evaluateHand(hand) == 0);
    }
}