#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>


class MockRobot
{
    private:
        std::string IPAddress;
        int port = 1000;
        SOCKET client;
        int sendCommand(std::string command);
        int sendCommand(std::string command, int location);
        
    public:
        MockRobot();
        bool isInitialized;
        void setIPAddress(std::string IPAdress);
        void setPort(int port);
        bool connect();
        bool disconnect();
        bool isConnected();
        int sendHome();
        int startPicking(int sourceLocation);
        int startPlacing(int destinationLocation);
        int transfer(int source, int destination);
        std::string getStatus(int processID);
};