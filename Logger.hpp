#ifndef LOGGER_HPP
#define LOGGER_HPP 



#include <iostream>
#include <string>
#include <fstream>
#include <complex>
#include <cstddef>
#include <stdexcept>

#include <vector>


#include <chrono>
#include <ctime>
#include <chrono>
#include <ctime>


void logDbgWithTime(std::string sFileName,std::string message);
void checkForTrucate(std::string sFileName,std::uintmax_t maxSize);



#endif

