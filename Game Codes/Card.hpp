#ifndef CARD_HPP
#define CARD_HPP

#include <string>

struct Card {
    std::string rank;
    std::string suit;
    
    int value;
};

#endif