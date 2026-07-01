#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../Blackjack.hpp"

TEST_CASE("Blackjack hand value calculation", "[blackjack]") {
    Blackjack game("Test", 1000);
    
    std::vector<Card> hand = {{"A", "Hearts"}, {"K", "Spades"}};
    REQUIRE(game.calculateHandValue(hand) == 21);

    hand = {{"A", "Hearts"}, {"9", "Spades"}, {"A", "Diamonds"}};
    REQUIRE(game.calculateHandValue(hand) == 21);

    hand = {{"5", "Hearts"}, {"7", "Spades"}, {"9", "Diamonds"}};
    REQUIRE(game.calculateHandValue(hand) == 21);

    hand = {{"2", "Clubs"}, {"3", "Diamonds"}, {"4", "Spades"}};
    REQUIRE(game.calculateHandValue(hand) == 9);
} 