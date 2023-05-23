#include "State.hpp"

// MENU STATE

MenuState::MenuState() {
}

MenuState::~MenuState() {
}

void MenuState::handle_inputs(Game& game) {
    game.set_mode(Modes::Online);
}

void MenuState::update(Game& game) {
}

void MenuState::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("C++ Tic-Tac-Toe", 190, 150, 40, BLACK);
    DrawText("[1] Play vs local opponent", 190, 200, 20, BLACK);
    DrawText("[2] Play vs AI opponent", 190, 230, 20, BLACK);
    DrawText("[3] Play vs online opponent", 190, 260, 20, BLACK);
    EndDrawing();
}

// MATCH STATE
// PAUSE STATE
