#include "Game.hpp"

Game::Game(unsigned int _width, unsigned int _height, std::string _title)
    : windowWidth(_width), windowHeight(_height)
{
    states.push_back(std::make_unique<MenuState>());
    InitWindow(_width, _height, _title.c_str());

    // in tic-tac-toe I don't need to go crazy with smooth 60FPS etc.
    EnableEventWaiting();
}

Game::~Game() {
    CloseWindow();
}

void Game::pushState(State* _state) {
    states.push_back(std::unique_ptr<State>(_state));
}

void Game::popState() {
    states.pop_back();
}

void Game::setShouldExit(bool _s) {
    shouldExit = _s;
}

unsigned int& Game::getWindowWidth() {
    return windowWidth;
}

unsigned int& Game::getWindowHeight() {
    return windowHeight;
}

HumanPlayer& Game::getPlayer() {
    return player;
}

std::unique_ptr<Player>&& Game::moveOpponent() {
    return std::move(opponent);
}

void Game::setOpponent(std::unique_ptr<Player>&& _opponent) {
    opponent = std::move(_opponent);
}

void Game::run() {
    while(!shouldExit) {
        // process input
        states.back()->handleInputs(*this);
        // update values
        states.back()->update(*this);
        // render
        states.back()->render(*this);
    }
}
