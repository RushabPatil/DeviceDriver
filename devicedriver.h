#include <iostream>
#include <string>
#include <vector>
#include "mockrobot.h"

class DeviceDriver
{
    private:
        MockRobot robot;

    public:
        DeviceDriver();
        std::string OpenConnection(std::string IPAddress);
        std::string CloseConnection();
        std::string Initialize();
        std::string ExecuteOperation(std::string operation, std::vector<std::string> paramNames, std::vector<int> paramValues);
        std::string Abort();
};