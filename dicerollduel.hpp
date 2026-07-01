#pragma once
#include "Game.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <random>

class dicerollduel : public Game{
    
public :
    dicerollduel(const std::string &playerName,double initialBalance);
    std::string getName() const;
    int rolldice();
    void play(double &playerBalance) override;

private :
    std :: string playerName;
    double initialBalance;
    std:: mt19937 gen;
};