#pragma once

#include "raylib.h"

class Player {
public:
    Player() {};
    ~Player();
    virtual int makeMove() = 0;
    virtual char& getMark() = 0;
    virtual const char* getName() = 0;

public:
    KeyboardKey pressedKey{KEY_ZERO};
};
