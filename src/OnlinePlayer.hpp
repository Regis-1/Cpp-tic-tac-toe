#pragma once

#include <memory>
#include "asio.hpp"
#include "Player.hpp"

typedef asio::ip::tcp tcp_ip;

class OnlinePlayer : public Player {
public:
    OnlinePlayer() = delete;
    OnlinePlayer(std::shared_ptr<tcp_ip::socket> _s);
    ~OnlinePlayer();

    int makeMove() override;
    char& getMark() override;
    const char* getName() override;

private:
    const char* name;
    char mark;

    std::shared_ptr<tcp_ip::socket> socket;
};
