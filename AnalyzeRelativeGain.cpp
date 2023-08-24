
#include "AnalyzeRelativeGain.hpp"
#include "Logger.hpp"

AnalyzeRelativeGain::AnalyzeRelativeGain(size_t totalBins,size_t binRange,float threshold) {
	iTotalNumBins = totalBins;
	iRangeOfBins = binRange;
	iCenterBin = totalBins / 2;
	iLowerBound = iCenterBin - (iRangeOfBins / 2);
	iUpperBound = iCenterBin + (iRangeOfBins / 2);
	fThreshold = threshold;
	bState = false;
	//logIt("ARG.txt",showObj());
}

bool AnalyzeRelativeGain::AddAndAnalyze(size_t binNumber,float f)
{
	if(binNumber >= iLowerBound && binNumber <= iUpperBound) {
		vValues.push_back(f);
		if(f > fThreshold) {
			bState = true;
		} 
	}

 	return true;
}

bool AnalyzeRelativeGain::IsFrameAJammer() {

 return bState;
}


void AnalyzeRelativeGain::logIt(std::string sFileName,std::string message) {
	std::uintmax_t maxSize = 200000;
    checkForTrucate(sFileName,maxSize);

    std::ofstream outputFile(sFileName.c_str(),std::ios::app);
    if(outputFile.is_open()) {
        outputFile<<message<<std::endl;
    }
    else {
        std::cout<<"Failed to open file: "<<sFileName<<std::endl;
    }
	outputFile.close();
}

void AnalyzeRelativeGain::logWithTime(std::string sFileName,std::string message) {
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
    logIt(sFileName,ss.str());
    

}





std::string AnalyzeRelativeGain::showObj() {
	std::stringstream ss;
	ss <<"iTotalNumBins: "<< iTotalNumBins <<std::endl;
	ss <<"iRangeOfBins: "<< iRangeOfBins <<std::endl;
	ss <<"iCenterBin: " << iCenterBin <<std::endl;
	ss <<"iLowerBound: "<< iLowerBound <<std::endl;
	ss <<"iUpperBound: "<< iUpperBound <<std::endl;
	
	ss <<"fThreshold: "<<fThreshold<<std::endl;
	ss <<"bState: "<<bState<<std::endl;
	if(vValues.size() > 0) {
		for(const auto& element : vValues) {
			ss<<"Element: "<<element<<std::endl;
		}
	}
	
	ss <<std::endl;
	return ss.str();
}

