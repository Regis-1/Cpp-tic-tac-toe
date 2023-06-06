#include "Game.hpp"
#include "MatchmakingState.hpp"

void startIoContext(asio::io_context& ioContext) { ioContext.run(); }

MatchmakingState::MatchmakingState() {
    pConnectionDetails.ipAddress = getLocalIP();
    pConnectionDetails.port = std::experimental::randint(6000, 7000);
    pConnectionDetails.ipAddressPrefix = "";

    pNetworkCode = encodeToHexCode(pConnectionDetails);

    TraceLog(LOG_INFO, pConnectionDetails.ipAddress.c_str());
    TraceLog(LOG_INFO, std::to_string(pConnectionDetails.port).c_str());

    acceptor = std::make_unique<tcp_ip::acceptor>(ioContext,
            tcp_ip::endpoint(tcp_ip::v4(), pConnectionDetails.port));

    acceptor->async_accept(socket, [this](const asio::error_code& ec){
        if(!ec) {
            TraceLog(LOG_INFO, "Connected with the opponent!");
            connected = true;
        }
        else
            TraceLog(LOG_ERROR, "Error with connection attempt.");
        });

    contextThread = std::thread{[&](){
        startIoContext(ioContext);
    }};
}

MatchmakingState::~MatchmakingState() {
    contextThread.join();
}

void MatchmakingState::handleInputs(Game& game) {
    int keyPressed = GetKeyPressed();
    bool keyPrintable = false;

    switch(keyPressed) {
        case KEY_ESCAPE:
            if(!isWriting)
                finishState = true;
            else
                isWriting = false;
            break;
        case KEY_ENTER:
            if(!isHosting && !isWriting)
                isWriting = true;
            break;
        case KEY_BACKSPACE:
            if(isWriting)
                if(oNetworkCode.size() > 1)
                    oNetworkCode.pop_back();
                else
                    oNetworkCode[0] = '_';
            break;
        case KEY_ONE:
            if(!isWriting)
                isHosting = !isHosting;
            else
                keyPrintable = true;
            break;
        case KEY_TWO:
            if(!isWriting)
                // try to connect
                connectToOpponent();
            else
                keyPrintable = true;
        default:
            if(isWriting && keyPressed >= KEY_ZERO && keyPressed <= KEY_F)
                keyPrintable = true;
    }

    if(keyPrintable)
        if(oNetworkCode == "_")
            oNetworkCode[0] = static_cast<char>(keyPressed);
        else
            oNetworkCode += static_cast<char>(keyPressed);
    keyPrintable = false;
}

void MatchmakingState::update(Game& game) {
    if(finishState) {
        game.popState();
        return;
    }
    if(connected) {
        game.setOpponent(std::make_unique<OnlinePlayer>(std::shared_ptr<tcp_ip::socket>(&socket)));
        game.pushState(new MatchState(game.getPlayer(), game.moveOpponent(),
                    std::shared_ptr<tcp_ip::socket>(&socket)));
        connected = false;
    } 
}

void MatchmakingState::render(Game& game) {
    std::string netCodeText = "Your online code: " + pNetworkCode;

    BeginDrawing();
    ClearBackground(RAYWHITE);
        drawTextCenteredH({netCodeText.c_str(), 100, 50, BLACK}, game.getWindowWidth());
    if(isHosting) {
        drawTextCenteredH({"[1] Connect to game", 250, 30, BLACK}, game.getWindowWidth());
        drawTextCenteredH({"Wait for someone to connect", 350, 30, BLACK}, game.getWindowWidth());
        drawTextCenteredH({"or connect to a game yourself", 380, 30, BLACK}, game.getWindowWidth());
    } else {
        drawTextCenteredH({"[1] Back", 230, 30, BLACK}, game.getWindowWidth());
        drawTextCenteredH({"[2] Connect", 280, 30, BLACK}, game.getWindowWidth());
        drawTextCenteredH({"Type other online code:", 350, 30, BLACK}, game.getWindowWidth());
        drawTextCenteredH({oNetworkCode.c_str(), 380, 30, isWriting ? RED : BLACK}, game.getWindowWidth());
        drawTextCenteredH({"Enter: writing mode, ESC: selection mode", 430, 20, BLACK}, game.getWindowWidth());
    }
    EndDrawing();
}

std::string MatchmakingState::getLocalIP() {
    std::string locIp;

    try {
        tcp_ip::resolver resolver(ioContext);
        tcp_ip::resolver::results_type endpoints = resolver.resolve("8.8.8.8", "443");
        asio::connect(socket, endpoints);
        asio::ip::address addr = socket.local_endpoint().address();
        locIp = addr.to_string();
        socket.close();
    } catch(const std::exception& e) {
        TraceLog(LOG_ERROR, e.what());
    }

    return locIp;
}

void MatchmakingState::connectToOpponent() {
    oConnectionDetails = decodeFromHexCode(oNetworkCode);
    try {
        socket.connect(tcp_ip::endpoint(asio::ip::address::from_string(oConnectionDetails.ipAddress), oConnectionDetails.port));
        connected = true;
    }
    catch(std::system_error& ec) {
        TraceLog(LOG_ERROR, ec.what());
    }
}

std::string MatchmakingState::encodeToHexCode(ConnectionDetails& input) {
    std::string _ipAddr = input.ipAddress;
    int _port = input.port;
    std::string delimiter = ".";

    std::vector<int> ipParts;
    std::string result = "";

    // to fix in the future
    size_t pos = 0;
    std::string token;
    int partCounter = 0;
    while((pos = _ipAddr.find(delimiter)) != std::string::npos) {
        token = _ipAddr.substr(0, pos);
        if(partCounter >= 2)
            ipParts.push_back(stoi(token));
        else
            input.ipAddressPrefix.append(token + ".");
        _ipAddr.erase(0, pos + delimiter.length());
        partCounter++;
    }
    ipParts.push_back(stoi(_ipAddr));

    for(auto n : ipParts) {
        result += intToHex(n);
    }

    result += intToHex(_port);
    
    // getting result to uppercase
    transform(result.begin(), result.end(), result.begin(), ::toupper);

    return result;
}

ConnectionDetails MatchmakingState::decodeFromHexCode(std::string input) {
    ConnectionDetails oDetails;
    if(input.size() != NETWORK_CODE_SIZE) {
        TraceLog(LOG_ERROR, "Wrong code size! Please provide valid network code.");
        return oDetails;
    }

    std::string hexes[3];
    hexes[0] = input.substr(0, 2);
    hexes[1] = input.substr(2, 2);
    hexes[2] = input.substr(4,4);

    int detailsParts[3];
    for(int i = 0; i < 3; i++)
        detailsParts[i] = hexToInt(hexes[i]);

    oDetails.ipAddressPrefix = pConnectionDetails.ipAddressPrefix;
    oDetails.ipAddress = oDetails.ipAddressPrefix + std::to_string(detailsParts[0]) + "." + std::to_string(detailsParts[1]);
    oDetails.port = detailsParts[2];

    return oDetails;
}

std::string MatchmakingState::intToHex(int input) {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << std::hex << input;
    return ss.str();
}

int MatchmakingState::hexToInt(std::string input) {
    int result;
    std::stringstream ss;
    ss << std::hex << input;
    ss >> result;

    return result;
}
