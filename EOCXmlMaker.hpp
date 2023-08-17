#ifndef EOCXMLMAKER_HPP
#define EOCXMLMAKER_HPP 

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>

namespace pt = boost::property_tree;

using namespace std;

struct debug_settings
{
    std::string m_file;               // log filename
    int m_level;                      // debug level
    std::set<std::string> m_modules;  // modules where logging is enabled
    void load(const std::string &filename);
    void save(const std::string &filename);
};

struct CGInfo 
{
    std::string id;
    std::string reader;
    std::string readerId;
    std::string domainIdStr;
    std::string cameraName;
    double lat;
    double lon;
    double errorradius;
    double velEast;
    double velNorth;
};

struct alarmInfo
{
    std::string alrmId;
    std::string alrmTimestamp;
    std::string hotListId;
    std::string hotListListId;
    std::string hotListRev;
    std::string hotlistListTypeId;
    std::string alrmStatus;
    int alrmDomainId;
    int alrmAlarmClassId2;
    std::string alrmCreateDate;
    std::string alrmBeginDate;
    std::string alrmEndDate;
    std::string alrmNotes;
    std::string alrmResultText;
    
    std::string readTimeStamp;
    std::string readPlate;
    std::string id;
    std::string reader;
    std::string readerId;
    std::string domainIdStr;
    std::string cameraName;
    double lat;
    double lon;
    double errorradius;
    double velEast;
    double velNorth;
};

struct consumerInfo
{
    int secsToWait;
    int lastAlarmSecsIgnore;

};

struct loggingInfo
{
    std::string jammerDbg;
    std::string notificationDbg;
    std::string spectralDbg;

};

struct eocInfo
{
    std::string eocHost;
    std::string eocUser;
    std::string eocPass;
    int eocPort;
};

class ReadAlarmXMLMaker
{
    public:
        string deriveXmlUS(CGInfo cgi,string plate,string timeStamp,string eocGuid);
        string deriveAlarmAndReadXMLUS(alarmInfo ai);
        string generateGUID();
        void testHarness();
        void testAlarmXML();

};

void xmlTest(std::string sInputFile,std::string sOutputFile);
void storeXMLInMemory(pt::ptree tree);



#endif