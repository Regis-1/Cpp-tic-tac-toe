#include "raylib.h"
#include "Game.hpp"

int main(void)
{
    Game game(800, 450, "C++ tic-tac-toe");
    game.run();

    return 0;
}
