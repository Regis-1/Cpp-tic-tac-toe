#include "Game.hpp"
#include "MatchState.hpp"

MatchState::MatchState(HumanPlayer& _player, std::unique_ptr<Player>&& _opponent,
            std::shared_ptr<tcp_ip::socket> _s)
    : player(_player), opponent(std::move(_opponent)), socket(_s)
{
    if(!socket)
        playerTurn = std::rand() % 2 == 0  ? true : false;
    else {
        int playerRandNum = std::rand();
        std::string msg = std::to_string(playerRandNum);

        asio::write(*socket, asio::buffer(msg));
        std::array<char, 16> response;
        response.fill('\0');
        socket->read_some(asio::buffer(response));

        int opponentRandNum = atoi(response.data());
        playerTurn = playerRandNum > opponentRandNum ? true : false;
    }
}

MatchState::~MatchState() {
    socket->close();
}

// HANDLE INPUTS
void MatchState::handleInputs(Game& game) {
    KeyboardKey pressedKey = (KeyboardKey)GetKeyPressed();
    if(pressedKey == KEY_ESCAPE) {
        game.popState();
    }
    else if(pressedKey >= KEY_ONE && pressedKey <= KEY_NINE) {
        if(playerTurn)
            player.pressedKey = pressedKey;
        else
            if(!socket)
                opponent->pressedKey = pressedKey;

        moveMade = false;
    }
}

// UPDATE
void MatchState::update(Game& game) {
    if(currentMatchResult == Result::Playing && !moveMade) {
        std::string m;

        int moveIdx = playerTurn ? player.makeMove() : opponent->makeMove();
        char& _mark = playerTurn ? player.getMark() : opponent->getMark();

        if(socket) {
            if(moveIdx == -1) {
                game.popState();
            }
            m = std::to_string(moveIdx);
            asio::write(*socket, asio::buffer(m));
        }

        if(mapChars[moveIdx] != player.getMark() && mapChars[moveIdx] != opponent->getMark()) {
            mapChars[moveIdx] = _mark;
            playerTurn = !playerTurn;
            moveMade = true;
            movesMade++;
        }

        currentMatchResult = checkWins();

        if(movesMade >= 9 && currentMatchResult == Result::Playing)
            currentMatchResult = Result::Tie;
    }
}

void MatchState::drawCharacter(unsigned int idx, char mark, Color color) {
    unsigned int x = CHAR_START_X;
    unsigned int y = CHAR_START_Y;
    const char* c = &mark;
    unsigned int row = idx / 3;

    DrawText(c, x + CELL_SIZE * (idx % 3), y + CELL_SIZE * (row % 3), 80, color);
}

void MatchState::drawMap() {
    for(auto l : mapLines) {
        DrawLineEx(l.start, l.end, MAP_LINES_WIDTH, BLACK);
    }

    unsigned int _mapCharsSize = sizeof(mapChars)/sizeof(char);

    for(unsigned int i = 0; i < _mapCharsSize; i++) {
        drawCharacter(i, mapChars[i], BLACK);
        if(currentMatchResult == Result::PlayerWon) {
            drawCharacter(wonMatch.p1, player.getMark(), RED);
            drawCharacter(wonMatch.p2, player.getMark(), RED);
            drawCharacter(wonMatch.p3, player.getMark(), RED);
        }
        else if(currentMatchResult == Result::OpponentWon) {
            drawCharacter(wonMatch.p1, opponent->getMark(), RED);
            drawCharacter(wonMatch.p2, opponent->getMark(), RED);
            drawCharacter(wonMatch.p3, opponent->getMark(), RED);
        }
    }
}

Result MatchState::checkWins() {
    char marks[2] = {player.getMark(), opponent->getMark()};
    for(unsigned int i = 0; i < 2; i++)
        for(auto w : mapWins) {
            if(mapChars[w.p1] == marks[i] && mapChars[w.p2] == marks[i] && mapChars[w.p3] == marks[i]) {
                wonMatch = w;
                return i == 0 ? Result::PlayerWon : Result::OpponentWon;
            }
        }

    return Result::Playing;
}

// RENDER
void MatchState::render(Game& game) {
    std::string textHeader = updateTextHeader();
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawTextCenteredH({textHeader.c_str(), 25, 40, BLACK},game.getWindowWidth());
    drawMap();
    EndDrawing();
}

std::string MatchState::updateTextHeader() {
    std::string _str = "'s turn";
    _str = playerTurn ? std::string(player.getName()) + _str : std::string(opponent->getName()) + _str;

    switch(currentMatchResult) {
        case Result::Playing:
            break;
        case Result::PlayerWon:
            _str = std::string(player.getName()) + " has won! ESC to main menu";
            break;
        case Result::OpponentWon:
            _str = std::string(opponent->getName()) + " has won! ESC to main menu";
            break;
        case Result::Tie:
            _str = "Tie, no winner! ESC to main menu";
            break;
    }

    return _str;
}
