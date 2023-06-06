#pragma once

#include "raylib.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "State.hpp"
#include "MenuState.hpp"
#include "HumanPlayer.hpp"

class Game {
public:
    Game() = delete;
    Game(unsigned int _width, unsigned int _height, std::string _title);
    ~Game();

    void run();
    void pushState(State* _state);
    void popState();
    void setShouldExit(bool _s);
    unsigned int& getWindowWidth();
    unsigned int& getWindowHeight();
    HumanPlayer& getPlayer();
    std::unique_ptr<Player>&& moveOpponent();
    void setOpponent(std::unique_ptr<Player>&& _opponent);

private:
    HumanPlayer player{"Player 1", 'x'};
    std::unique_ptr<Player> opponent{nullptr};
    bool shouldExit{false};
    unsigned int windowWidth;
    unsigned int windowHeight;
    std::vector<std::unique_ptr<State>> states;
};
