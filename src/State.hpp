#pragma once

#include "raylib.h"

#include <memory>
#include <string>

class Game;

enum Modes {
    NotDefined,
    Local,
    Ai,
    Online
};

struct TextLine {
    const char* content;
    unsigned int y;
    unsigned int fontSize;
    Color color;
};

struct Line {
    Vector2 start;
    Vector2 end;
};

// STATE
class State {
public:
    virtual void handleInputs(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void render(Game& game) = 0;
    void drawTextCenteredH(TextLine line, unsigned int windowWidth);
};

// PAUSE STATE
class PauseState : public State {
};
