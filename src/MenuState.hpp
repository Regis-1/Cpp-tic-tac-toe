#pragma once

class Game;
#include "State.hpp"
#include "MatchState.hpp"
#include "MatchmakingState.hpp"

class MenuState : public State {
public:
    MenuState();
    ~MenuState();

    void handleInputs(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

public:
    Modes mode{Modes::NotDefined};
};
