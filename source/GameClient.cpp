
#include <iostream>
#include "GameClient.h"

GameClient::GameClient(const sf::IpAddress& ip,unsigned short port)
    //:recievedData({sf::Vector2f(0.f,0.f),sf::Vector2f(0.f,0.f),sf::Vector2f(0.0f, 0.0f), false})
{
    m_connected=false;
    m_running2=true;
//connection(ip,port);
    t1=std::thread(&GameClient::connection,this,ip,port);
    t1.detach();
}

GameClient::~GameClient() {
    m_running2=false;
//m_socket.disconnect();
}

void GameClient::connection(const sf::IpAddress& ip, unsigned short port)
{
    unsigned short initPort = port;
    while (!m_connected){
        static int checkLoop=0;
        if (m_socket.connect(ip, port, sf::seconds(5)) != sf::Socket::Done)
        {
            if(checkLoop<2) {
	            std::cout << "Error connecting to port " << port <<std::endl;
	            port++;
                checkLoop++;
            }
            else
            {
                checkLoop = 0;
                port = initPort;
                std::cout << "Error connecting to server" << std::endl;
            }
        }
        else {
            m_connected = true;
            std::cout << "Connected to the server" << std::endl;
//            sf::Packet NameP;
//            m_socket.receive(NameP);
//            m_mutex.lock();
//            NameP>>Name;
//            m_mutex.unlock();
        }
    }
    while (this->m_running2 && m_connected ) {
        this->recievedData  = recieveData();
    }

}

const std::string &GameClient::getName() const {
    return Name;
}

const playerController &GameClient::getRecievedData() const {
    return recievedData;
}

playerController GameClient::recieveData(){
    m_socket.setBlocking(true);
//    while(m_running2)
//    {
        playerController controller;
        sf::Packet Sam;

        if (m_socket.receive(Sam) == sf::Socket::Done) {
            Sam >> controller.isPressedLeft >> controller.isPressedRight >> controller.isPressedUp >>
                controller.isLeftMouseButtonPressed >> controller.isRightMouseButtonPressed >>
                controller.mousePosition.x >> controller.mousePosition.y;
            return controller;
        } else
        {
            //std::cout << "No data recieved";
          return controller;
        }
   // }
}

