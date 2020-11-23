
#include <SFML/Network.hpp>
#include <iostream>
#include "GameServer.h"
#include <SFML/Graphics.hpp>
#include "playerController.h"
#include <SFML/Network/TcpSocket.hpp>

GameServer::GameServer(unsigned short port)
{
    m_running = true;
    listenPort(port);
//        std::cout << "Error - Failed to bind the port " << port << std::endl;

}

int GameServer::getM_playersConnected() const {
    return m_playersConnected;
}

GameServer::~GameServer(){
    m_running = false;
    socket.disconnect();
    m_listener.close();
}
void GameServer::listenPort(unsigned short port)
{
    if(m_listener.listen(port) == sf::Socket::Done)
    {
        std::cout << "Server is started on port: " << port <<  ". Waiting for clients.\n";
        m_selector.add(m_listener);
        m_playersConnected = 0;
        m_dataWaiting = false;
        t0 = std::thread(&GameServer::receive, this);
        t0.detach();
    }
    else
    {
        listenPort(++port);
    }
}

void GameServer::receive() {
    while (m_running) {
        while (m_playersConnected == 0) {
            if (m_listener.accept(this->socket) == sf::Socket::Done) {
//                sf::Packet Name;
//                Name<<player_name;
//                socket.send(Name);
                ++m_playersConnected;
                std::cout<<"Client is connected "<<std::endl;
            }
        }
//        std::cout<<"Data:"<<m_dataWaiting<<std::endl;
        if (this->m_dataWaiting){
            std::cout << "Sending data"<< std::endl;
            if (socket.send(this->m_toSend) != sf::Socket::Done)
                std::cout << "Error sending KeyPress" << std::endl;
            m_mutex.lock();
            this->m_dataWaiting = false;
            m_mutex.unlock();
        }
    }
}

playerController convertPacketToInfo(sf::Packet packet){
    playerController controller;
    packet >> controller.isPressedLeft >> controller.isPressedRight >> controller.isPressedUp >>
        controller.isLeftMouseButtonPressed >> controller.isRightMouseButtonPressed >>
        controller.mousePosition.x >> controller.mousePosition.y;
    return controller;
}

void GameServer::update(playerController controller) {
    sf::Packet keyPress;
    keyPress << controller.isPressedLeft << controller.isPressedRight << controller.isPressedUp <<
        controller.isLeftMouseButtonPressed << controller.isRightMouseButtonPressed <<
        controller.mousePosition.x << controller.mousePosition.y;  

    playerController c1 = convertPacketToInfo(keyPress);
    playerController c2 = convertPacketToInfo(this->m_toSend);
    if (c1.isLeftMouseButtonPressed!=c2.isLeftMouseButtonPressed ||
        c1.isPressedLeft!=c2.isPressedLeft ||
        c1.isPressedRight!=c2.isPressedRight ||
        c1.isPressedUp!=c2.isPressedUp ||
        c1.isRightMouseButtonPressed!=c2.isRightMouseButtonPressed ||
        c1.mousePosition!=c2.mousePosition) {
        this->m_toSend = keyPress;
        m_mutex.lock();
        this->m_dataWaiting = true;
        m_mutex.unlock();
    }
}

