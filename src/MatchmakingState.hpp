#pragma once

#include <sstream>
#include <iomanip>
#include <algorithm>
#include <experimental/random>
#include <memory>
#include <thread>
#include "asio.hpp"

class Game;
#include "State.hpp"
#include "OnlinePlayer.hpp"

struct ConnectionDetails {
    std::string ipAddress;
    std::string ipAddressPrefix;
    int port;
};

typedef asio::ip::tcp tcp_ip;

const unsigned int NETWORK_CODE_SIZE = 8;

class MatchmakingState : public State {
public:
    MatchmakingState();
    ~MatchmakingState();

    void handleInputs(Game& game) override;
    void update(Game& game) override;
    void render(Game& game) override;

private:
    std::string getLocalIP();
    void connectToOpponent();
    std::string encodeToHexCode(ConnectionDetails& input);
    ConnectionDetails decodeFromHexCode(std::string input);
    std::string intToHex(int input);
    int hexToInt(std::string input);

private:
    bool finishState{false};
    bool isHosting{true};
    bool isWriting{false};
    bool connected{false};

    ConnectionDetails pConnectionDetails;
    ConnectionDetails oConnectionDetails;
    std::string pNetworkCode;
    std::string oNetworkCode{"_"};

    asio::io_context ioContext;
    tcp_ip::socket socket{ioContext};
    std::unique_ptr<tcp_ip::acceptor> acceptor;
    std::thread contextThread;
};
