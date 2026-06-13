#include <iostream>
#include <memory>
#include <string>
#include "CasinoManager.hpp" // CasinoManager handles all game logic and is extensible for new games

using namespace std;

int main() {
    string playerName;
    int playerAge;
    double initialAmount;

    cout << "\n==== Welcome to CLI Casino ====\n";

    cout << "Enter your name: ";
    getline(cin, playerName);

    cout << "Enter your age: ";
    cin >> playerAge;

    if (playerAge < 18) {
        cout << "Access denied. You must be at least 18 years old to enter the casino.\n";
        return 0;
    }

    cout << "Enter the amount of money you want to play with: $";
    cin >> initialAmount;

    cin.ignore(); 
    // CasinoManager manages player info, balance, and game selection
    shared_ptr<CasinoManager> manager = make_shared<CasinoManager>(playerName, playerAge, initialAmount);
    manager->start();

    return 0;
}
