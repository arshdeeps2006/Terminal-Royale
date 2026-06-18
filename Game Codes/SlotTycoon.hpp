#pragma once
#include "Game.hpp"
#include <string>
#include <vector>
#include <random>

class SlotTycoon : public Game {

public:
    SlotTycoon(const std::string& playerName, double initialBalance);
    void play(double& balance) override;
    std::string getName() const override;

private:
    std::string playerName;
    int machineLevel;
    int totalSpins;
    int totalWins;
    double totalInvested;
    double totalReturned;

    std::uniform_real_distribution<double> dist{0.0, 1.0};
    std::mt19937 rng;

    void showMenu() const;
    void printRules() const;
    void upgradeMachine(double& balance);
    void spinMachine(double& balance);
    double getPayoutMultiplier() const;
    double getWinProbability() const;
    void showStats() const;
};
