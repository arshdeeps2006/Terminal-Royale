#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "dicerollduel.hpp"
#include <string>

dicerollduel :: dicerollduel(const std::string &name,double balance)
    : playerName(name), initialBalance(balance) ,gen(std::random_device{}()) {}

std::string dicerollduel::getName() const {
    return "Dice Roll Duel";
}

int dicerollduel::rolldice() {
    // Create a uniform distribution for dice rolls (1 to 6) and return a random number
    std::uniform_int_distribution<> dist(1, 6);
    return dist(gen);
}

void dicerollduel :: play(double& playerBalance){
    std::cout << "\n--- Welcome to Dice Roll Duel, " << playerName << "! ---\n";
    std::cout << "In this game, you and the dealer will each roll two dice.\nThe player with the higher total wins the round.\n";
    
    // Ask the player for their bet and validate it
    double bet;
    std::cout << "Your current balance: $" << playerBalance << std::endl;
    
    while (true) {
        std::cout << "Enter your bet: $";
        std::cin >> bet;
        
        if (std::cin.fail() || bet <= 0 || bet > playerBalance) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Dealer: Nice try! Place a valid bet within your balance.\n" << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break; 
        }
    }

    int playerDie1 = rolldice();
    int playerDie2 = rolldice();
    int dealerDie1 = rolldice();
    int dealerDie2 = rolldice();

    int playerScore = playerDie1 + playerDie2;
    int dealerScore = dealerDie1 + dealerDie2;

    std::cout << "You rolled: " << playerDie1 << " and " << playerDie2 << " (Total: " << playerScore << ")\n";
    std::cout << "Dealer rolled: " << dealerDie1 << " and " << dealerDie2 << " (Total: " << dealerScore << ")\n";

    if (playerScore > dealerScore) {
        std::cout << "Dealer: You win! Beginner’s luck or skill?\n";
        playerBalance += bet;
    } else if (playerScore < dealerScore) {
        std::cout << "Dealer: I win! Lady Luck is on my side today.\n";
        playerBalance -= bet;
    } else {
        std::cout << "Dealer: It's a tie! Guess we both have lucky hands.\n";
    }
    std::cout << "New balance: $" << playerBalance << std::endl;
}