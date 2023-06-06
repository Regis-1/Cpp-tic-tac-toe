#include "State.hpp"

void State::drawTextCenteredH(TextLine line, unsigned int windowWidth) {
    int textWidth = MeasureText(line.content, line.fontSize);
    unsigned int _x = windowWidth / 2 - textWidth / 2;
    DrawText(line.content, _x, line.y, line.fontSize, line.color);
}

// PAUSE STATE
