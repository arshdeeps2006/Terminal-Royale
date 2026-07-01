#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Game.hpp defines the base class for all games in the casino,
// which CasinoManager will manage and allow the player to play. 
#include "Game.hpp"

class CasinoManager {
public:
    // CONSTRUCTOR TO INITIALIZE PLAYER INFO AND STARTING BALANCE
    CasinoManager(const std::string& name, int age, double balance); 
    void start();
private:
    // PLAYER INFORMATION AND BALANCE TRACKING
    std::string playerName;
    int playerAge;
    double playerBalance;
    double initialBalance;

    // VECTOR TO HOLD ALL AVAILABLE GAMES IN THE CASINO. THIS ALLOWS FOR EASY EXTENSIBILITY BY ADDING NEW GAMES TO THE VECTOR.
    std::vector<std::shared_ptr<Game>> games;

    // PRIVATE HELPER FUNCTIONS FOR CASINO OPERATIONS
    void showMenu();
    void addGame(const std::shared_ptr<Game>& game);
    void printProfitLoss() const;
}; 
