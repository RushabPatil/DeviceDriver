
#include "devicedriver.h"

DeviceDriver::DeviceDriver() {}

std::string DeviceDriver::OpenConnection(std::string IPAddress) {
    
    robot.setIPAddress(IPAddress);
    robot.connect();

    return "";

}

std::string DeviceDriver::CloseConnection() 
{
     Enter("OpenConnection");
    robot.disconnect();
    return " ";
}

std::string DeviceDriver::Initialize() 
{   
    Enter("Initialize");
    Require(Called("OpenConnection"));
    robot.sendHome();
    return "";
}

std::string DeviceDriver::ExecuteOperation(const std::string operation, std::vector<std::string> paramNames, std::vector<int> paramValues) 
{
    int sourceLocation = 0;
    int destinationLocation = 0;

    for(int i = 0; i < paramNames.size(); i++)
    {
        if(paramNames[i] == "Source Location")
        {
            sourceLocation = paramValues[i];
        }
        else if (paramNames[i] == "Destination Location")
        {
            destinationLocation = paramValues[i];
        }
        
    }

    if(operation == "pick")
    {
        robot.startPicking(sourceLocation);
    }
    else if(operation == "place")
    {
        robot.startPlacing(destinationLocation);
    }
    else if(operation == "transfer")
    {
        robot.transfer(sourceLocation, destinationLocation);
    }
    else
    {
        robot.sendHome();
    }
    
    return "";
}

std::string DeviceDriver::Abort() 
{
    if(CloseConnection() == "")
    {
        return "";
    }
   
    return "CloseConnection failed";
}
