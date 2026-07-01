#include "ThreeCardPoker.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

ThreeCardPoker::ThreeCardPoker(const std::string& name, double& balance)
    : playerName(name), playerBalance(balance) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

std::string ThreeCardPoker::getName() const {
    return "Three Card Poker";
}

void ThreeCardPoker::printRules() const {
    std::cout << "\n--- RULES ---\n";
    std::cout << "1. You will be dealt 3 cards, each with a value from 1 to 13.\n";
    std::cout << "2. Winning combinations:\n";
    std::cout << "   - Three of a Kind: All three cards are the same (payout 10 times)\n";
    std::cout << "   - Straight: Cards are in sequence (e.g., 4,5,6) (payout 6 times)\n";
    std::cout << "   - Pair + Near Sequence: A pair plus a card that is one away from the pair (e.g., 5,5,6) (payout 4 times)\n";
    std::cout << "   - Pair: Two cards are the same (payout 2 times)\n";
    std::cout << "3. If you don't have any of the above combinations, you lose your bet.\n";
}

int ThreeCardPoker::evaluateHand(const std::vector<int>& cards) {
    // Check for Three of a Kind
    if (cards[0] == cards[1] && cards[1] == cards[2]) {
        std::cout << "Superbbb !  Three of a Kind!\n";
        return 10;
    }
    // Check for Straight
    else if (cards[2] == cards[1] + 1 && cards[1] == cards[0] + 1) {
        std::cout << "Awesommeee !  Straight!\n";
        return 6;
    }
    // Check for Pair + near-sequence
    else if (
        (cards[0] == cards[1] && std::abs(cards[0] - cards[2]) == 1) ||
        (cards[1] == cards[2] && std::abs(cards[2] - cards[0]) == 1)
    ) {
        std::cout << "You got ( Pair + Near Sequence!)\n";
        return 4;
    }
    // Check for Pair
    else if (cards[0] == cards[1] || cards[1] == cards[2] || cards[0] == cards[2]) {
        std::cout << "Hahhh Pair!\n";
        return 2;
    }
    // High Card
    else {
        std::cout << "Ooops High Card. No win.\n";
        return 0;
    }
}

void ThreeCardPoker::play(double& dummy) {
    (void)dummy;

    std::cout << "\n== Welcome to Three Card Poker, ==" << playerName << "!\n";
    printRules();
    std::cout << "Your current balance: $" << playerBalance << "\n";

    double betAmount;
    // Loop continuously until the player gives a valid bet
    while (true) {
        std::cout << "Enter Your bet : $";
        std::cin >> betAmount;
        
        if (std::cin.fail() || betAmount <= 0 || betAmount > playerBalance) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Dealer: Invalid bet! Please enter a valid number within your balance." << std::endl;
        } else {
            break; 
        }
    }

    std::vector<int> cards(3);
    for (int& card : cards) {
        card = (std::rand() % 13) + 1; 
    }

    std::sort(cards.begin(), cards.end());

    std::cout << " Your cards are : ";
    for (int c : cards) std::cout << c << " ";
    std::cout << "\n";

    int payoutMultiplier = evaluateHand(cards);

    if (payoutMultiplier > 0) {
        double winnings = betAmount * payoutMultiplier;
        std::cout << "Congrats ,  You win $" << winnings << "!\n";
        playerBalance += (winnings - betAmount); // net profit added
    } else {
        std::cout << " Ah Try Again Dude , You lost $" << betAmount << ".\n";
        playerBalance -= betAmount;
    }

    std::cout << "Your New balance: $" << playerBalance << "\n";
}
