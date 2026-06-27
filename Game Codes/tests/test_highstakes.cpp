
#include "catch.hpp"
#include "../Highstakes.hpp"

TEST_CASE("card value calculation","[Highstakes]"){
    Highstakes game("Test",100);
     
        
        REQUIRE(game.cardValue("A") == 14);
        REQUIRE(game.cardValue("K") == 13);
        REQUIRE(game.cardValue("Q") == 12);
        REQUIRE(game.cardValue("J") == 11);
        REQUIRE(game.cardValue("10") == 10);
        REQUIRE(game.cardValue("9") == 9);
        REQUIRE(game.cardValue("8") == 8);
        REQUIRE(game.cardValue("7") == 7);
        REQUIRE(game.cardValue("6") == 6);
        REQUIRE(game.cardValue("5") == 5);
        REQUIRE(game.cardValue("4") == 4);
        REQUIRE(game.cardValue("3") == 3);
        REQUIRE(game.cardValue("2") == 2);
        
        // CHECK FOR INVALID INPUTS 
        REQUIRE(game.cardValue("1") == -1);
        REQUIRE(game.cardValue("X") == -1);
        REQUIRE(game.cardValue("AB") == -1);
}