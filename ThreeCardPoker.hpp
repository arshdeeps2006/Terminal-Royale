#pragma once
#include "Game.hpp"
#include <string>
#include <vector>

class ThreeCardPoker : public Game {
public:
    ThreeCardPoker(const std::string& name, double& balance);
    std::string getName() const override;
    int evaluateHand(const std::vector<int>& cards);
    void play(double& dummy) override;
private:
    void printRules() const;
    std::string playerName;
    double& playerBalance;
};
