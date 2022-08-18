#include "mockrobot.h"

MockRobot::MockRobot()
{
    IPAddress = "";
    port = 0;
}


void MockRobot::setIPAddress(std::string IPAdress)
{
    this->IPAddress = IPAdress;
}

void MockRobot::setPort(int port)
{
    this -> port = port;
}


void MockRobot::connect()
{
    //make a connection with the robot software
}

void MockRobot::disconnect()
{
    //disconnect with the robot
}

int MockRobot::sendCommand(std::string command)
{
    //send command over command over TCP/IP network
}

int MockRobot::sendCommand(std::string command, int location)
{
    //send command over command over TCP/IP network
}

std::string MockRobot::robotStatus(std::string command, int processID)
{
    //send command over command over TCP/IP network
}

int MockRobot::sendHome()
{
    return sendCommand("home");
}

int MockRobot::startPicking(int sourceLocation)
{
    return sendCommand("pick", sourceLocation);
}

int MockRobot::startPlacing(int destinationLocation)
{
    return sendCommand("place", destinationLocation);
}

std::string MockRobot::getStatus(int processId)
{
    std::string status = robotStatus("status", processId);
    return status;
}