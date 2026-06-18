#include "Highstakes.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>
#include <limits>

Highstakes::Highstakes(const std::string& name, double balance)
    : playerName(name), initialBalance(balance) {}

std::string Highstakes::getName() const {
    return "Highstakes";
}

void Highstakes::printCard(const Card& card) const {
    std::cout << card.rank << " of " << card.suit << " (value " << card.value << ")" << std::endl;
}

int Highstakes::cardValue(const std::string &rank) const {
    if (rank == "A") {
        return 14;
    }
    else if (rank == "Q") {
        return 12;
    }
    else if (rank == "K") return 13;
    else if (rank == "J") return 11;
    else return std::stoi(rank);
}

void Highstakes::initializeDeck() {
    static const std::vector<std::string> ranks = {
        "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"
    };
    static const std::vector<std::string> suits = {
        "Hearts", "Diamonds", "Clubs", "Spades"
    };
    
    deck.clear();
    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            deck.push_back({rank, suit, cardValue(rank)});
        }
    }
}

void Highstakes::shuffleDeck() {
    // XORing with the system clock bypasses compiler bugs with random_device
    static std::mt19937 gen(std::random_device{}() ^ 
        std::chrono::system_clock::now().time_since_epoch().count());
    
    std::shuffle(deck.begin(), deck.end(), gen);
}

Card Highstakes::dealCard() {
    Card card = deck.back();
    deck.pop_back();
    return card;
}

void Highstakes::play(double& playerBalance) {
    std::cout << "Hey there, " << playerName << "! Welcome to Highstakes.." << std::endl;
    std::cout << "Let me quickly explain the rules:\nYou and I will each draw a card from the deck.\nThe one with the higher card wins the round.\nIf we draw cards of equal value, it's a tie!" << std::endl;
    std::cout << "Your current balance is : $" << playerBalance << std::endl;
    
    double bet;
    
    // Loop continuously until the player gives a valid bet
    while (true) {
        std::cout << "Enter Your bet : $";
        std::cin >> bet;
        
        if (std::cin.fail() || bet <= 0 || bet > playerBalance) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Dealer: Invalid bet! Please enter a valid number within your balance." << std::endl;
        } else {
            break; 
        }
    }
    
    initializeDeck();
    shuffleDeck();
    
    Card playerCard = dealCard();
    Card dealerCard = dealCard();
    
    std::cout << "Your card is : ";
    printCard(playerCard);
    std::cout << std::endl;
    
    std::cout << "Dealer's card is : ";
    printCard(dealerCard);
    std::cout << std::endl;
    
    int playerval = playerCard.value;
    int dealerval = dealerCard.value;
    
    if (playerval > dealerval) {
        std::cout << "Dealer: You win! You're riding high on luck today!" << std::endl;
        playerBalance += bet;
    }
    else if (playerval < dealerval) {
        std::cout << "Dealer : I win!! The house always smiles.." << std::endl;
        playerBalance -= bet;
    }
    else {
        std::cout << "Dealer : It's a Tie!! Luck's playing fair today." << std::endl;
    } 
    
    std::cout << "Your current Balance : $" << playerBalance << std::endl;
}