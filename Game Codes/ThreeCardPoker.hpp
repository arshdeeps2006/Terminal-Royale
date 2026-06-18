#pragma once
#include "Game.hpp"
#include <string>

class ThreeCardPoker : public Game {
public:
    ThreeCardPoker(const std::string& name, double& balance);
    std::string getName() const override;
    void play(double& dummy) override;
private:
    void printRules() const;
    std::string playerName;
    double& playerBalance;
};
