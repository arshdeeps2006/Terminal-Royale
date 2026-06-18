#include "CasinoManager.hpp"
#include <iostream>

// Provides blueprints for all mini-games to the casino manager
#include "Blackjack.hpp"
#include "SlotTycoon.hpp"
#include "Highstakes.hpp"
#include "ThreeCardPoker.hpp"
#include "dicerollduel.hpp"

CasinoManager::CasinoManager(const std::string& name, int age, double balance)
    : playerName(name), playerAge(age), playerBalance(balance), initialBalance(balance) {
    // Add available games here
    // NOTE: Each game is derived from the base class Game, allowing for polymorphic behavior
    addGame(std::make_shared<Blackjack>(playerName, playerBalance));
    addGame(std::make_shared<SlotTycoon>(playerName, playerBalance));
    addGame(std::make_shared<Highstakes>(playerName,playerBalance));
    addGame(std::make_shared<ThreeCardPoker>(playerName, playerBalance));
    addGame(std::make_shared<dicerollduel>(playerName, playerBalance));    
}

void CasinoManager::addGame(const std::shared_ptr<Game>& game) {
    games.push_back(game);
}

void CasinoManager::showMenu() {
    std::cout << "\nAvailable Games:" << std::endl;
    for (int i = 0; i < games.size(); i++) {
        std::cout << i + 1 << ". " << games[i]->getName() << std::endl;
    }
    std::cout << games.size() + 1 << ". Exit" << std::endl;
}

void CasinoManager::printProfitLoss() const {
    double diff = playerBalance - initialBalance;
    if (diff > 0) {
        std::cout << "\nDealer: Whoa! You made a profit of $" << diff << ". Drinks are on you!" << std::endl;
    } else if (diff < 0) {
        std::cout << "\nDealer: Ouch! You lost $" << -diff << ". Better luck next time!" << std::endl;
    } else {
        std::cout << "\nDealer: You broke even! That's rare!" << std::endl;
    }
}

void CasinoManager::start() {
    bool running = true;
    while (running) {
        showMenu();
        std::cout << "Select the game number you want to play (or " << games.size() + 1 << " to exit): ";
        int choice;
        std::cin >> choice;
        if (choice < 1 || choice > static_cast<int>(games.size()) + 1) {
            std::cout << "Invalid choice. Try again." << std::endl;
            continue;
        }
        if (choice == static_cast<int>(games.size()) + 1) {
            printProfitLoss();
            std::cout << "Thank you for visiting the casino!" << std::endl;
            break;
        }
        games[choice - 1]->play(playerBalance);
    }
} 