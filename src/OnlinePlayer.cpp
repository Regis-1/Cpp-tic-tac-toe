#include "OnlinePlayer.hpp"

OnlinePlayer::OnlinePlayer(std::shared_ptr<tcp_ip::socket> _s)
    : socket(std::move(_s)), name("Opnt"), mark('o') {

}

OnlinePlayer::~OnlinePlayer() {
}

int OnlinePlayer::makeMove() {
    asio::error_code ec;
    std::array<char, 1> responseMove;
    socket->read_some(asio::buffer(responseMove), ec);
    if(ec == asio::error::eof)
        return -1;
    return atoi(responseMove.data());
}

char& OnlinePlayer::getMark() {
    return mark;
}

const char* OnlinePlayer::getName() {
    return name;
}
