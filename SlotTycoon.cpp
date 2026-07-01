#include "SlotTycoon.hpp"
#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>

SlotTycoon::SlotTycoon(const std::string& playerName, double initialBalance)
    : playerName(playerName), machineLevel(1), totalSpins(0), totalWins(0),
      totalInvested(0), totalReturned(0), rng(std::chrono::system_clock::now().time_since_epoch().count()) {}

std::string SlotTycoon::getName() const {
    return "Virtual Slot City Tycoon";
}

void SlotTycoon::showMenu() const {
    std::cout << "\n--- Slot Tycoon Menu ---\n";
    std::cout << "1. Spin the Slot Machine\n";
    std::cout << "2. Upgrade Machine (Cost: $" << machineLevel * 300 << ")\n";
    std::cout << "3. View Stats\n";
    std::cout << "4. Exit\n";
}

void SlotTycoon::upgradeMachine(double& balance) {
    double cost = machineLevel * 300;
    if (balance >= cost) {
        balance -= cost;
        totalInvested += cost; 
        machineLevel++;
        std::cout << "Machine upgraded to Level " << machineLevel << "!\n";
    } else {
        std::cout << "Not enough balance to upgrade.\n";
    }
}

double SlotTycoon::getWinProbability() const {
    return 0.2 + (machineLevel * 0.05); // Level 1: 25%, Level 2: 30%, etc.
}

double SlotTycoon::getPayoutMultiplier() const {
    return 2.0 + (machineLevel * 0.5); // Level 1: 2.5x, Level 2: 3x, etc.
}

void SlotTycoon::spinMachine(double& balance) {
    double bet;
    std::cout << "Enter bet amount: $";
    std::cin >> bet;

    if (std::cin.fail() || bet <= 0 || bet > balance) {
        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
        std::cout << "Invalid bet. Please enter a valid number within your balance.\n";
        return; 
    }

    double roll = dist(rng);
    balance -= bet;
    totalSpins++;
    totalInvested += bet;

    if (roll < getWinProbability()) {
        double winAmount = bet*getPayoutMultiplier();
        balance += winAmount;
        totalReturned += winAmount;
        totalWins++;
        std::cout << "You WIN! Payout: $" << std::fixed << std::setprecision(2) << winAmount << "\n";
    } else {
        std::cout << "No luck. You lost the bet.\n";
    }
}

void SlotTycoon::showStats(double balance) const {
    std::cout << "\n--- Tycoon Stats ---\n";
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    std::cout << "Machine Level: " << machineLevel << "\n";
    std::cout << "Total Spins: " << totalSpins << "\n";
    std::cout << "Total Wins: " << totalWins << "\n";
    std::cout << "Win Rate: " << (totalSpins > 0 ? (100.0 * totalWins / totalSpins) : 0) << "%\n";
    std::cout << "Total Invested: $" << totalInvested << "\n";
    std::cout << "Total Returned: $" << totalReturned << "\n";
    std::cout << "ROI: " << (totalInvested > 0 ? (100.0 * totalReturned / totalInvested) : 0) << "%\n";
}

void SlotTycoon::printRules() const {
    std::cout << "\n--- RULES ---" << std::endl;
    std::cout << "1. Spin the slot machine and try to win money." << std::endl;
    std::cout << "2. Betting: You can place a bet for each spin. The bet amount will be deducted from your balance in case of a loss." << std::endl;
    std::cout << "3. If you win, your bet will be multiplied by the payout multiplier based on your machine level to calculate your reward after a win." << std::endl;
    std::cout << "4. Upgrading: You can upgrade your machine to increase your chances of winning and the payout multiplier." << std::endl;
    std::cout << "5. Stats: You can view your stats, including total spins, wins, and ROI." << std::endl;
}

void SlotTycoon::play(double& balance) {
    std::cout << "\nWelcome, " << playerName << " | Balance: $" << std::fixed << std::setprecision(2) << balance << "\n";
    printRules();

    bool keepPlaying = true;
    while (keepPlaying) {
        showMenu();

        int choice;
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input. Please enter a number.\n";
            continue; 
        }

        switch (choice) {
            case 1:
                spinMachine(balance);
                break;
            case 2:
                upgradeMachine(balance);
                break;
            case 3:
                showStats(balance);
                break;
            case 4:
                keepPlaying = false;
                break;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}
