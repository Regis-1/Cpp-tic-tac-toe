#include "Game.hpp"

Game::Game(unsigned int _width, unsigned int _height, std::string _title)
    : windowWidth(_width), windowHeight(_height), mode{Modes::Local}
{
    states.push_back(std::make_unique<MenuState>());
    InitWindow(_width, _height, _title.c_str());
}

Game::~Game() {
    CloseWindow();
}

void Game::set_mode(Modes _mode) {
    mode = _mode;
}

void Game::run() {
    while(!WindowShouldClose()) {
        // process input
        states.back()->handle_inputs(*this);
        // update values
        states.back()->update(*this);
        // render
        states.back()->render();
    }
}
