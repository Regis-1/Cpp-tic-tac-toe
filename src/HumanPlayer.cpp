#include "HumanPlayer.hpp"

HumanPlayer::HumanPlayer(const char* _name, char _mark)
    : name(_name), mark(_mark)
{}

HumanPlayer::~HumanPlayer() {}

int HumanPlayer::makeMove() {
    return pressedKey % KEY_ONE; // mod to normalize - from 0 to 9
}

char& HumanPlayer::getMark() {
    return mark;
}

const char* HumanPlayer::getName() {
    return name;
}
