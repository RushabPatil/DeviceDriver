#include "mockrobot.h"

MockRobot::MockRobot()
{
    IPAddress = "";
    isInitialized = false;
}

void MockRobot::setIPAddress(std::string IPAdress)
{
    this->IPAddress = IPAdress;
}

void MockRobot::setPort(int port)
{
    this -> port = port;
}


bool MockRobot::connect()
{
    //make a connection with the robot software
    // client socket program
    return false;
}

bool MockRobot::disconnect()
{
    //disconnect with the robot
    // close the socket
    return false;
}

int MockRobot::sendCommand(std::string command)
{
    //send command over command over TCP/IP network
    std::string request = command;
}

int MockRobot::sendCommand(std::string command, int location)
{
    //send command over command over TCP/IP network
    std::string request = command + "%" + to_string(location);
}

std::string MockRobot::robotStatus(std::string command, int processID)
{
    //send command over command over TCP/IP network
    std::string request = command + "%" + to_string(processID);
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


int MockRobot::transfer(int source, int destination)
{
    int pickProcess = startPicking(source);
    if(getStatus(pickProcess)=="complete")
    {
        int placeProcess = startPlacing(destination);
        
        return placeProcess;

    }

    return pickProcess;
}

std::string MockRobot::getStatus(int processId)
{
    return robotStatus("status", processId); 
}