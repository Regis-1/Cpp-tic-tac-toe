#pragma once

#include "raylib.h"

#include <memory>

#include "Game.hpp"

class Game;

class State {
public:
    virtual void handle_inputs(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void render() = 0;
};

class MenuState : public State {
public:
    MenuState();
    ~MenuState();

    void handle_inputs(Game& game) override;
    void update(Game& game) override;
    void render() override;
};

class MatchState : public State {
};

class PauseState : public State {
};
