#pragma once

#include <memory>
#include <cstdlib>
#include <ctime>
#include <string>
#include <array>

#include "raylib.h"
#include "asio.hpp"

struct WinMatch {
    int p1;
    int p2;
    int p3;
};

enum Result {
    PlayerWon,
    OpponentWon,
    Tie,
    Playing
};

class Game;
#include "State.hpp"
#include "HumanPlayer.hpp"

const unsigned int CHAR_START_X = 225;
const unsigned int CHAR_START_Y = 140;
const unsigned int CELL_SIZE = 150;
const float MAP_LINES_WIDTH = 8.0f;

typedef asio::ip::tcp tcp_ip;

class MatchState : public State {
public:
    MatchState() = delete;
    MatchState(HumanPlayer& _player, std::unique_ptr<Player>&& _opponent,
            std::shared_ptr<tcp_ip::socket> _s = nullptr);

    ~MatchState();

    void handleInputs(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    bool findOnlineOpponent() { return true; }
    bool acquireAiOpponent() { return true; }
    void drawCharacter(unsigned int idx, char mark, Color color);
    void drawMap();
    Result checkWins();

    //renderHelpers
    std::string updateTextHeader();

private:
    HumanPlayer& player;
    std::unique_ptr<Player> opponent;
    std::shared_ptr<tcp_ip::socket> socket;

    bool moveMade{true};
    bool playerTurn;
    WinMatch wonMatch;
    Result currentMatchResult{Result::Playing};
    unsigned int movesMade{0};

    Modes mode;
    Line mapLines[4] = {
        {{325, 100}, {325, 550}},
        {{475, 100}, {475, 550}},
        {{175, 250}, {625, 250}},
        {{175, 400}, {625, 400}}
    };
    char mapChars[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    WinMatch mapWins[8] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };
};
