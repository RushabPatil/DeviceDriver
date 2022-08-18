#include "mockrobot.h"
#include "devicedriver.h"


int main(int argc, char const *argv[])
{
    DeviceDriver driver;
    MockRobot robot;

    //dummy IP address
    std::string dummyIP = "192.168.1.1";
   
    //Add IP Address 
    driver.OpenConnection(dummyIP);

    if(driver.Initialize() == "")
    {
        std::cout << "Initialize successful" << std::endl;
    }
  
    while(driver.Abort() != "")
    {
        //Execute any operation here
       
    }

    return 0;
}
