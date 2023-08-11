#ifndef CONFIGDATA_HPP
#define CONFIGDATA_HPP 

#include "EOCXmlMaker.hpp"

namespace pt = boost::property_tree;

using namespace std;

struct ConfigData
{
    alarmInfo ai;
    consumerInfo ci;
    bool loadConfig(string sXmlPath,string dbgFile);
    string showConfig();
};


#endif