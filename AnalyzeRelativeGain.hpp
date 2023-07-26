#ifndef ANALYZE_RELATIVE_GAIN_HPP
#define ANALYZE_RELATIVE_GAIN_HPP 

#include <complex>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>


class AnalyzeRelativeGain {

 private:
	size_t iLowerBound;
	size_t iUpperBound;
	size_t iRangeOfBins;
	size_t iTotalNumBins;
	size_t iCenterBin;
	std::vector<float> vValues;
	float fThreshold;
	bool bState;
  
 public:
 	AnalyzeRelativeGain(size_t totalBins,size_t binRange,float threshold);
	bool AddAndAnalyze(size_t binNumber,float f);
	bool IsFrameAJammer();
	void logIt(std::string sFileName,std::string message);
	std::string showObj();
	void logWithTime(std::string sFileName,std::string message);

 
};



#endif /*ANALYZE_RELATIVE_GAIN_HPP*/




