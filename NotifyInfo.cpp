#include "NotifyInfo.hpp"


bool FileNotify::sendNotify(NotifyInfo ni) 
{
	
	return logIt(ni.sNotifyFile,ni.sMessage);
}


bool FileNotify::logIt(std::string sFileName,std::string message)
{
	std::stringstream ss;
	
	//Get the current system time
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    // Convert the system time to a duration since the epoch
    std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    // Convert the system time to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    // Convert the time_t object to a string representation
    std::string timeString = std::ctime(&currentTime);
    ss <<currentTime<<"."<<duration.count()<<" :"<<message<<std::endl;
    
    std::ofstream outputFile(sFileName.c_str(),std::ios::app);
    if(outputFile.is_open()) {
        outputFile<<ss.str()<<std::endl;
    }
    else {
        std::cout<<"Failed to open file: "<<sFileName<<std::endl;
    }
	
	return true;
}
