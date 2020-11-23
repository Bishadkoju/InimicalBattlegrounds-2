
#pragma once
#include <thread>
#include "playerController.h"
#include <SFML/Network.hpp>

class GameClient {

public:
    GameClient(const sf::IpAddress& ip, unsigned short port);
    void connection(const sf::IpAddress& ip, unsigned short port);
    playerController recieveData();
    bool isConnected() { return m_connected; }
    virtual ~GameClient();
    const playerController &getRecievedData() const;

    const std::string &getName() const;

private:
    sf::TcpSocket m_socket;
    bool m_connected;
    bool m_running2;
    std::string Name;
    playerController recievedData;
    std::thread t1;
};
