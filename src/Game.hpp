#pragma once

#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "State.hpp"

class State;

enum Modes {
    Local,
    Ai,
    Online
};

class Game {
public:
    Game() = delete;
    Game(unsigned int _width, unsigned int _height, std::string _title);
    ~Game();

    void run();
    void set_mode(Modes _mode);

private:
    unsigned int windowWidth;
    unsigned int windowHeight;
    Modes mode;
    std::vector<std::unique_ptr<State>> states;
};
