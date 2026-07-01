#include <iostream>
#include <memory>
#include <string>

// CasinoManager handles all game logic and is extensible for new games
#include "CasinoManager.hpp" 

int main() {
    std::string playerName;
    int playerAge;
    double initialAmount;

    std::cout << "\n===== Welcome to Terminal Royale! =====" << std::endl;

    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);

    std::cout << "Enter your age: ";
    std::cin >> playerAge;

    if (playerAge < 18) {
        std::cout << "Access denied. You must be at least 18 years old to enter the casino." << std::endl;
        return 0;
    }

    std::cout << "Enter the amount of money you want to play with: $";
    std::cin >> initialAmount;

    std::cin.ignore(); 
    // CasinoManager manages player info, balance, and game selection
    std::shared_ptr<CasinoManager> manager = std::make_shared<CasinoManager>(playerName, playerAge, initialAmount);
    manager->start();

    return 0;
}