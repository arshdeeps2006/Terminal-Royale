# Terminal Royale
A collection of classic casino games, reimagined for your terminal. Built in modern C++ with a clean, extensible architecture and add your own games in minutes.
---
## Prerequisites

Before you begin, ensure you have the following installed on your system:
* **A C++17 compatible compiler** (GCC/MinGW, Apple Clang, or MSVC)
* **[CMake](https://cmake.org/download/)** (Version 3.10 or higher)
* **Git** 
---

## Features

- Multiple casino games playable from a single menu
- Simple `Game` interface for plugging in new games
- CMake-based build system
- Unit tests included

## Setup & Build

**Clone and enter the project:**
```sh
git clone https://github.com/arshdeeps2006/Terminal-Royale.git
cd Terminal-Royale
```

**Build with CMake:**
Choose the build commands that match your operating system and compiler:

*For Mac and Linux:*
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

*For Windows(MinGW):*
```sh
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

*For Windows (Visual Studio/MSVC):*
```sh
mkdir build
cd build
cmake ..
cmake --build .
```

*Launch the casino:*
```sh
./casino
```

**Run the test suite:**
```sh
./tests
```

## Building Your Own Game

Every game in Terminal Royale plugs into the same `Game` interface, so adding a new one is straightforward.

**Step 1 : Create your files**

Drop `YourGame.hpp` and `YourGame.cpp` into the project, and have your class extend `Game`:

```cpp
#include "Game.hpp"

class YourGame : public Game {
public:
    YourGame(const std::string& playerName, double initialBalance);
    void play(double& playerBalance) override;
    std::string getName() const override;
    // your custom game logic goes here
};
```

**Step 2 : Write the logic**

Fill in the constructor, `play()`, and `getName()` inside `YourGame.cpp`.

**Step 3 : Hook it into the menu**

Open `CasinoManager.cpp`, include your header, and register the game:

```cpp
#include "YourGame.hpp"
// ...
addGame(std::make_shared<YourGame>(playerName, playerBalance));
```

**Step 4 : Tell CMake about it**

Add the new source file to `add_executable` in `CMakeLists.txt`:

**Step 5 : (Optional) Add tests**

Drop a test file in `tests/` covering your game's logic.

**Step 6 : Rebuild**

```sh
cmake --build build
```

Your game now shows up in the casino menu. 

## Project Structure

A quick mental model of how things fit together:
- `Game.hpp` — the base interface every game implements
- `CasinoManager` — owns and runs the menu of available games
- Individual game files (e.g. `Blackjack.cpp`) — self-contained game logic
- `tests/` — unit tests for game logic

---

Place your bets :)
