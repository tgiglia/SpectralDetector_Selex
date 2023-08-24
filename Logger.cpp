#include "Logger.hpp"


void logDbgWithTime(std::string sFileName,std::string message)
{
	std::stringstream ss;
	//make sure the file has not exceeded the maxsize
    std::uintmax_t maxSize = 200000;
    checkForTrucate(sFileName,maxSize);

	//Get the current system time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    // Convert the system time to a duration since the epoch
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    // Convert the system time to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    
    char timeBuffer[80];
    struct tm *timeInfo = localtime(&currentTime);
    strftime(timeBuffer,sizeof(timeBuffer),"%Y-%m-%d %H:%M:%S",timeInfo);
    
    ss <<timeBuffer<<"."<<duration.count()<<": "<<message<<std::endl;
    
    std::ofstream outputFile(sFileName.c_str(),std::ios::app);
    if(outputFile.is_open()) {
        outputFile<<ss.str()<<std::endl;
    }
    else {
        std::cout<<"Failed to open file: "<<sFileName<<std::endl;
    }
    outputFile.close();
}


void checkForTrucate(std::string sFileName,std::uintmax_t maxSize)
{
    std::ifstream file(sFileName, std::ios::binary | std::ios::ate);

    if (!file) 
    {        
        return;
    }

    std::streampos fileSize = file.tellg(); // Get the current position, which is the file size
    file.close();
    if(fileSize > maxSize) 
    {
        //we have to truncate
        std::ofstream file(sFileName, std::ios::trunc);
        // Close the file to truncate it
        file.close();
    }

}