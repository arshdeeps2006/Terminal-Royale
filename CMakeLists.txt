cmake_minimum_required(VERSION 3.10)   # Sets the minimum required CMake version
project(TerminalRoyale)                # Names the overall project build as TerminalRoyale

set(CMAKE_CXX_STANDARD 17)             # Forces the compiler to use the C++17 standard

add_executable(casino                  # Creates executable named "casino"
    main.cpp                           # Entry point
    CasinoManager.cpp                  # Game manager
    Blackjack.cpp                      # Blackjack implementation
    SlotTycoon.cpp                     # Slot machine game
    Highstakes.cpp                     # Highstakes game
    ThreeCardPoker.cpp                 # Three-card poker
    dicerollduel.cpp                   # Dice duel game
)

add_executable(tests                   # Creates executable named "tests" for running test cases
    tests/test_blackjack.cpp           # Unit tests for Blackjack
    Blackjack.cpp                      # Blackjack implementation under test

    tests/test_highstakes.cpp          # Unit tests for Highstakes
    Highstakes.cpp                     # Highstakes implementation under test

    tests/test_slottycoon.cpp          # Unit tests for Highstakes
    SlotTycoon.cpp                     # Highstakes implementation under test

    tests/test_drd.cpp          # Unit tests for Highstakes
    dicerollduel.cpp                     # Highstakes implementation under test

    tests/test_threecardpoker.cpp          # Unit tests for Highstakes
    ThreeCardPoker.cpp                     # Highstakes implementation under test
)
