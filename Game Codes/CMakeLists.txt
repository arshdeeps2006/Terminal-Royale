cmake_minimum_required(VERSION 3.10)
project(CasinoCLI)

set(CMAKE_CXX_STANDARD 17)

add_executable(casino
    main.cpp
    CasinoManager.cpp
    Blackjack.cpp
    SlotTycoon.cpp
    Highstakes.cpp
    ThreeCardPoker.cpp
    dicerollduel.cpp
)

add_executable(tests
    tests/test_blackjack.cpp
    Blackjack.cpp
    tests/test_highstakes.cpp
    Highstakes.cpp
) 
