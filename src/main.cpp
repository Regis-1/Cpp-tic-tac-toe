#include "raylib.h"

#include "Game.hpp"

int main(void)
{
    std::srand(std::time(nullptr));

    Game game(800, 600, "C++ tic-tac-toe");
    game.run();

    return 0;
}
