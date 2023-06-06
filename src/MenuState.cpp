#include "Game.hpp"
#include "MenuState.hpp"

MenuState::MenuState() {
}

MenuState::~MenuState() {
}

void MenuState::handleInputs(Game& game) {
    if(IsKeyPressed(KEY_ONE)) {
        mode = Modes::Local;
    }
    else if(IsKeyPressed(KEY_TWO)) {
        mode = Modes::Ai;
    }
    else if(IsKeyPressed(KEY_THREE)) {
        mode = Modes::Online;
    }
    else if(IsKeyPressed(KEY_ESCAPE)) {
        game.setShouldExit(true);
    }
}

void MenuState::update(Game& game) {
    switch(mode) {
        case Modes::Local:
            game.setOpponent(std::make_unique<HumanPlayer>("Player 2", 'o'));
            game.pushState(new MatchState(game.getPlayer(), game.moveOpponent()));
            break;
        case Modes::Ai:
            break;
        case Modes::Online:
            game.pushState(new MatchmakingState());
            break;
    }
    mode = Modes::NotDefined;
}

void MenuState::render(Game& game) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawTextCenteredH({"C++ Tic-Tac-Toe", 100, 80, BLACK}, game.getWindowWidth());
    drawTextCenteredH({"[1] Play vs local opponent", 300, 40, BLACK}, game.getWindowWidth());
    drawTextCenteredH({"[2] Play vs AI opponent", 350, 40, BLACK}, game.getWindowWidth());
    drawTextCenteredH({"[3] Play vs online opponent", 400, 40, BLACK}, game.getWindowWidth());
    EndDrawing();
}
