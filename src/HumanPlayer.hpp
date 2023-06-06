#pragma once

#include "Player.hpp"

class HumanPlayer : public Player {
public:
    HumanPlayer() = delete;
    HumanPlayer(const char* _name, char mark);
    ~HumanPlayer();

    int makeMove() override;
    char& getMark() override;
    const char* getName() override;

private:
    const char* name;
    char mark;
};
