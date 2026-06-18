#pragma once
#include "Game.hpp"
#include <vector>
#include <string>
#include "Card.hpp"

class Highstakes: public Game {
private:
    std::string playerName;
    double initialBalance;
    std::vector<Card> deck;

    void initializeDeck();
    void shuffleDeck();
    Card dealCard();
    
    void printCard(const Card& card) const;
public :
    Highstakes(const std::string& playerName, double initialBalance);
    int cardValue(const std::string &rank) const;
    std::string getName() const override;
    void play(double& playerBalance) override;

};
