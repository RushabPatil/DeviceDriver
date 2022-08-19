
#include "devicedriver.h"

DeviceDriver::DeviceDriver() {}

/**
 * @brief 
 * 
 * @param IPAddress 
 * @return std::string 
 */
std::string DeviceDriver::OpenConnection(std::string IPAddress) 
{   
    robot.setIPAddress(IPAddress);
    if(robot.connect()) {
        return "Connection established";
    }
    else {
        return "Connection failed. Check IP address or port number.";
    }

}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string DeviceDriver::Abort() 
{
    if(robot.disconnect()) {
        return "Connection Terminated";
    }
    else {
        return "Connection termination failed. Please try again.";
    }
}


/**
 * @brief 
 * 
 * @return std::string 
 */
std::string DeviceDriver::Initialize() 
{   
    if(!robot.isConnected())
    {
        return "Robot is not connected. Please connect to the robot again.";
    }
    else
    {
        return "Robot is connected. Initializing the robot...";
    }

    while (robot.isInitialized == false)
    {
        currentProcessID = robot.sendHome();
        if(robot.getStatus(currentProcessID) == "Terminated with error")
        {
            return "Couldn't finish the action. Please try again.";
        }
        else if (robot.getStatus(currentProcessID) == "In Progress") 
        {
            return "Robot is initializing....";
        }
        else(robot.getStatus(currentProcessID) == "FinishedSuccessfully")
        {
            robot.isInitialized = true;
            return "";
        }
    }
    
}


/**
 * @brief 
 * 
 * @param operation 
 * @param paramNames 
 * @param paramValues 
 * @return std::string 
 */
std::string DeviceDriver::ExecuteOperation(const std::string operation, std::vector<std::string> paramNames, std::vector<int> paramValues) 
{
    Enter("ExecuteOperation");

    if(!robot.isConnected())
    {
        return "Robot is not connected. Please connect to the robot again.";
    }

    if(!robot.isInitialized)
    {
        return "Robot is not initialized. Please initialize the robot to execute any operations.";
    }

    if(currentProcessID < 0) {
        
        return "Other operation is in progress. Another operation cannot be executed until the current operation is completed.";
    }

    if(operation != "pick" || operation != "place" || operation != "transfer" || operation != "status" || operation != "home") 
    {
      
        return "Invalid operation. Please choose from pick, place, or trasnfer operations.";
    }

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

    if(operation == "home")
    {
        currentProcessID = robot.sendHome();
    }
    else if(operation == "pick")
    {
        currentProcessID = robot.startPicking(sourceLocation);
    }
    else if(operation == "place")
    {
        currentProcessID = robot.startPlacing(destinationLocation);
    }
    else if(operation == "transfer")
    {
        currentProcessID = robot.transfer(sourceLocation, destinationLocation);
    }
    else(operation == "status")
    {
         if(robot.getStatus(currentProcessID) == "Terminated with error")
        {
            return "Couldn't finish the action. Please try again.";
        }
        else if (robot.getStatus(currentProcessID) == "FinishedSuccessfully")
        {
            return "" ;
        }
        else
        {
            return "Task in progress";
        }   
    }
  
}
