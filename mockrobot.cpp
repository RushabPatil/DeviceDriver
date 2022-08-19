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


/**
 * @brief 
 * 
 * @return bool 
 */
bool MockRobot::connect()
{
    // Initialize Winsock
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        std::cout << "WSAStartup function failed with error: %d\n" << iResult << std::endl;
        return false;
    }

    // Create a client SOCKET for connecting to robot's server
    client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        std::cout << "connect function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        WSACleanup();
    }   

    // The sockaddr_in structure specifies the address family,
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(IPAddress.c_str());
    clientService.sin_port = htons(port);


    // Connect to server on robot software
    iResult = connect(client, (SOCKADDR *) & clientService, sizeof (clientService));
    if (iResult == SOCKET_ERROR) {
        std::cout << "connect function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        iResult = closesocket(client);
        if (iResult == SOCKET_ERROR)
            std::cout << "closesocket function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    std::out << "Connected to the robot..." << std::endl;

    return true;
}


/**
 * @brief 
 * 
 * @return bool 
 */
bool MockRobot::disconnect()
{
    //disconnect with the robot
    // close the socket
    int iResult = closesocket(client);
    if (iResult == SOCKET_ERROR) 
    {
        std::cout << "closesocket function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }
    
    std::cout << "Robot disconnected" << std::endl;
    return true;
}


bool isConnected()
{
    int recvbuf_len = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN] = "";

    //send command over command over TCP/IP network
    std::string request = "isConnected";

    int iResult = send(client, request.c_str(), (int)strlen(request.c_str()), 0 );
    if (iResult == SOCKET_ERROR) 
    {
        std::cout << "send function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        closesocket(client);
        WSACleanup();
        std::cout << "Connection closed. Reconnect with the robot." << std::endl;
        return false;

    }

    iResult = recv(client, recvbuf, recvbuf_len, 0);
    if (iResult > 0) 
       return true;
    else if (iResult == 0)
        return false;
    else
        std::cout << "recv function failed with error: %ld\n" << WSAGetLastError() << std::endl;

}


/**
 * @brief 
 * 
 * @return bool 
 */
int MockRobot::sendCommand(std::string command)
{

    int recvbuf_len = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN] = "";

    //send command over command over TCP/IP network
    std::string request = command;

    int iResult = send(client, request.c_str(), (int)strlen(request.c_str()), 0 );
    if (iResult == SOCKET_ERROR) 
    {
        std::cout << "send function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        closesocket(client);
        WSACleanup();
        std::cout << "Connection closed. Reconnect with the robot." << std::endl;
        return 0;

    }

    // Receive until the peer closes the connection
    do 
    {
        iResult = recv(client, recvbuf, recvbuf_len, 0);
        if (iResult > 0) 
        {
            return (int)recvbuf;
        }
        else if (iResult == 0)
            std::cout << "Connection closed. Reconnect with the robot." << std::endl;
        else
            std::cout << "recv function failed with error: %ld\n" << WSAGetLastError() << std::endl;

    } while( iResult > 0 );
}


/**
 * @brief 
 * 
 * @return bool 
 */
int MockRobot::sendCommand(std::string command, int location)
{
    int recvbuf_len = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN] = "";

    //send command over command over TCP/IP network
    std::string request = command + "%" + std::to_string(location);

    int iResult = send(client, request.c_str(), (int)strlen(request.c_str()), 0 );
    if (iResult == SOCKET_ERROR) 
    {
        std::cout << "send function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        closesocket(client);
        WSACleanup();
        std::cout << "Connection closed. Reconnect with the robot." << std::endl;
        return 0;

    }

    // Receive until the peer closes the connection
    do 
    {
        iResult = recv(client, recvbuf, recvbuf_len, 0);
        if (iResult > 0) 
        {
            return (int)recvbuf;
        }
        else if (iResult == 0)
            std::cout << "Connection closed. Reconnect with the robot." << std::endl;
        else
            std::cout << "recv function failed with error: %ld\n" << WSAGetLastError() << std::endl;

    } while( iResult > 0 );
}



/**
 * @brief 
 * 
 * @return std::string 
 */
std::string MockRobot::getStatus(int processID)
{
    int recvbuf_len = DEFAULT_BUFLEN;
    char recvbuf[DEFAULT_BUFLEN] = "";

     //send command over command over TCP/IP network
    std::string request = "status" + "%" + std::to_string(processID);

    int iResult = send(client, request.c_str(), (int)strlen(request.c_str()), 0 );
    if (iResult == SOCKET_ERROR) 
    {
        std::cout << "send function failed with error: %ld\n" << WSAGetLastError() << std::endl;
        closesocket(client);
        WSACleanup();
        std::cout << "Connection closed. Reconnect with the robot." << std::endl;
        return 0;

    }

    // Receive until the peer closes the connection
    do 
    {
        iResult = recv(client, recvbuf, recvbuf_len, 0);
        if (iResult > 0) 
        {
            return (int)recvbuf;
        }
        else if (iResult == 0)
            std::cout << "Connection closed. Reconnect with the robot." << std::endl;
        else
            std::cout << "recv function failed with error: %ld\n" << WSAGetLastError() << std::endl;

    } while( iResult > 0 );
}


/**
 * @brief 
 * 
 * @return bool 
 */
int MockRobot::sendHome()
{
    return sendCommand("home");
}



/**
 * @brief 
 * 
 * @return bool 
 */
int MockRobot::startPicking(int sourceLocation)
{
    return sendCommand("pick", sourceLocation);
}


/**
 * @brief 
 * 
 * @return bool 
 */
int MockRobot::startPlacing(int destinationLocation)
{
    return sendCommand("place", destinationLocation);
}


/**
 * @brief 
 * 
 * @return bool 
 */
int MockRobot::transfer(int source, int destination)
{
    int pickProcess = startPicking(source);
    if(getStatus(pickProcess)=="FinishedSuccessfully")
    {
        int placeProcess = startPlacing(destination);
        
        return placeProcess;

    }

    return pickProcess;
}