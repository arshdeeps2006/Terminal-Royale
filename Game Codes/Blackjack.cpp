#include "Blackjack.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <chrono> 
#include <limits> 

// Card.hpp Defines the structure of a playing card, including its rank, suit, and value.
#include "Card.hpp"

Blackjack::Blackjack(const std::string& name, double balance)
    : playerName(name), initialBalance(balance) {}

std::string Blackjack::getName() const {
    return "Blackjack";
}

void Blackjack::initializeDeck() {
    static const std::vector<std::string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    static const std::vector<std::string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    deck.clear();
    for (const auto& suit : suits) {
        for (const auto& rank : ranks) {
            deck.push_back({rank, suit});
        }
    }
}


void Blackjack::shuffleDeck() {
    // Static ensures the generator is only created and seeded once
    // XORing with the system clock ensures true randomness even on broken compilers
    static std::mt19937 gen(std::random_device{}() ^ std::chrono::system_clock::now().time_since_epoch().count());
    
    std::shuffle(deck.begin(), deck.end(), gen);
}

Card Blackjack::dealCard() {
    Card card = deck.back();
    deck.pop_back();
    return card;
}

int Blackjack::calculateHandValue(const std::vector<Card>& hand) const {
    int value = 0;
    int aces = 0;
    for (const auto& card : hand) {
        if (card.rank == "A") {
            value += 11;
            aces++;
        } else if (card.rank == "K" || card.rank == "Q" || card.rank == "J") {
            value += 10;
        } else {
            value += std::stoi(card.rank);
        }
    }
    // Handle aces
    while (value > 21 && aces > 0) {
        value -= 10;
        aces--;
    }
    return value;
}

void Blackjack::printHand(const std::vector<Card>& hand, bool hideFirstCard) const {
    for (int i = 0; i < hand.size(); i++) {
        if (i == 0 && hideFirstCard) {
            std::cout << "[Hidden], ";
        } else {
            std::cout << hand[i].rank << " of " << hand[i].suit;
            if (i != hand.size() - 1) std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

void Blackjack::printRules() const {
    std::cout << "\n--- BLACKJACK RULES ---" << std::endl;
    std::cout << "1. The Goal: Beat the dealer's hand without your card total going over 21." << std::endl;
    std::cout << "2. Card Values: Number cards (2-10) are worth face value. Face cards (J, Q, K) are worth 10. Aces are 1 or 11." << std::endl;
    std::cout << "3. The Deal: You and the dealer both start with two cards. One of the dealer's cards remains hidden." << std::endl;
    std::cout << "4. Your Turn: You can choose to 'Hit' (take another card) as many times as you like or 'Stand' (keep your current hand)." << std::endl;
    std::cout << "5. Busting: If your cards total more than 21, you 'bust' and lose your bet automatically." << std::endl;
    std::cout << "6. Dealer's Turn: The dealer reveals their hidden card and must hit until their total is 17 or higher." << std::endl;
    std::cout << "7. Winning: You win if your total is higher than the dealer's without busting, or if the dealer busts." << std::endl;
    std::cout << "8. Blackjack: Getting exactly 21 on your first two cards is a 'Blackjack' and is an instant win!" << std::endl;
    std::cout << "-----------------------\n" << std::endl;
}

void Blackjack::play(double& playerBalance) {
    std::cout << "\n--- Welcome to Blackjack, " << playerName << "! ---" << std::endl;
    printRules();
    double bet;
    std::cout << "Your current balance: $" << playerBalance << std::endl;
    
    while (true) {
        std::cout << "Enter your bet: $";
        std::cin >> bet;
        
        if (std::cin.fail() || bet <= 0 || bet > playerBalance) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Dealer: Trying to rob the casino, eh? Place a valid bet within your balance!" << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break; 
        }
    }

    initializeDeck();
    shuffleDeck();

    std::vector<Card> playerHand, dealerHand;
    playerHand.push_back(dealCard());
    dealerHand.push_back(dealCard());
    playerHand.push_back(dealCard());
    dealerHand.push_back(dealCard());

    // Show hands
    std::cout << "Dealer's hand: ";
    printHand(dealerHand, true);
    std::cout << "Your hand: ";
    printHand(playerHand, false);

    // Right after printing the initial hands:
    if (calculateHandValue(playerHand) == 21) {
        std::cout << "Dealer: Blackjack! Beginners luck..." << std::endl;
        playerBalance += (bet * 1.5); 
        std::cout << "New balance: $" << playerBalance << std::endl;
        return; 
    }

    // Player turn
    while (true) {
        int playerValue = calculateHandValue(playerHand);
        if (playerValue > 21) {
            std::cout << "Dealer: Busted! Did you think you were playing Go Fish?" << std::endl;
            playerBalance -= bet;
            break;
        }

        std::cout << "Your hand value: " << playerValue << std::endl;
        std::cout << "Hit or stand? (h/s): ";
        char choice;
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'h' || choice == 'H') {
            playerHand.push_back(dealCard());
            std::cout << "Dealer: Bold move! You drew: " << playerHand.back().rank << " of " << playerHand.back().suit << std::endl;
        } else if (choice == 's' || choice == 'S') {
            std::cout << "Dealer: Standing already? Let's see what I've got..." << std::endl;
            break;
        } else {
            std::cout << "Dealer: I don't speak Martian. Please enter 'h' or 's'." << std::endl;
        }
    }

    // Dealer turn
    std::cout << "Dealer's hand: ";
    printHand(dealerHand, false);
    int dealerValue = calculateHandValue(dealerHand);
    while (dealerValue < 17) {
        dealerHand.push_back(dealCard());
        std::cout << "Dealer: Hitting myself... I drew: " << dealerHand.back().rank << " of " << dealerHand.back().suit << std::endl;
        dealerValue = calculateHandValue(dealerHand);
    }
    std::cout << "Dealer's final hand value: " << dealerValue << std::endl;

    int playerValue = calculateHandValue(playerHand);
    std::cout << "Your final hand value: " << playerValue << std::endl;

    // Determine winner
    if (playerValue > 21) {
        std::cout << "Dealer: You bust! The house thanks you for your donation." << std::endl;
        playerBalance -= bet;
    } else if (dealerValue > 21 || playerValue > dealerValue) {
        std::cout << "Dealer: You win! Did you bring a rabbit's foot?" << std::endl;
        playerBalance += bet;
    } else if (playerValue < dealerValue) {
        std::cout << "Dealer: I win! Don't worry, luck is just a state of mind." << std::endl;
        playerBalance -= bet;
    } else {
        std::cout << "Dealer: Push! It's a tie. Even I can't win every time." << std::endl;
    }
    std::cout << "New balance: $" << playerBalance << std::endl;
} 
