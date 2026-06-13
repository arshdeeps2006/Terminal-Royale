#include "CasinoManager.hpp"
#include <iostream>

// PULLING BLUEPRINTS OF THE MINI-GAMES
#include "Blackjack.hpp"
#include "SlotTycoon.hpp"
#include "Highstakes.hpp"
#include "ThreeCardPoker.hpp"
#include "dicerollduel.hpp"

using namespace std;

CasinoManager::CasinoManager(const string& name, int age, double balance)
    : playerName(name), playerAge(age), playerBalance(balance), initialBalance(balance) {
    // Add available games here
    addGame(make_shared<Blackjack>(playerName, playerBalance));
    addGame(make_shared<SlotTycoon>(playerName, playerBalance));
    addGame(make_shared<Highstakes>(playerName,playerBalance));
    addGame(make_shared<ThreeCardPoker>(playerName, playerBalance));
    addGame(make_shared<dicerollduel>(playerName, playerBalance));    
}

void CasinoManager::addGame(const shared_ptr<Game>& game) {
    games.push_back(game);
}

void CasinoManager::showMenu() {
    cout << "\nAvailable Games:\n";
    for (int i = 0; i < games.size(); i++) {
        cout << i + 1 << ". " << games[i]->getName() << "\n";
    }
    cout << games.size() + 1 << ". Exit\n";
}

void CasinoManager::printProfitLoss() const {
    double diff = playerBalance - initialBalance;
    if (diff > 0) {
        cout << "\nDealer: Whoa! You made a profit of $" << diff << ". Drinks are on you!\n";
    } else if (diff < 0) {
        cout << "\nDealer: Ouch! You lost $" << -diff << ". Better luck next time!\n";
    } else {
        cout << "\nDealer: You broke even! That's rare!\n";
    }
}

void CasinoManager::start() {
    bool running = true;
    while (running) {
        showMenu();
        cout << "Select a game: ";
        int choice;
        cin >> choice;
        if (choice < 1 || choice > static_cast<int>(games.size()) + 1) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }
        if (choice == static_cast<int>(games.size()) + 1) {
            printProfitLoss();
            cout << "Thank you for visiting the casino!\n";
            break;
        }
        games[choice - 1]->play(playerBalance);
    }
} 

 