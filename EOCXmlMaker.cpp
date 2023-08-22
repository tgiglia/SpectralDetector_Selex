#include "EOCXmlMaker.hpp"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace std;

void debug_settings::load(const std::string &filename)
{
    // Create empty property tree object
    pt::ptree tree;

    // Parse the XML into the property tree.
    pt::read_xml(filename, tree);

    // Use the throwing version of get to find the debug filename.
    // If the path cannot be resolved, an exception is thrown.
    m_file = tree.get<std::string>("debug.filename");

    // Use the default-value version of get to find the debug level.
    // Note that the default value is used to deduce the target type.
    m_level = tree.get("debug.level", 0);

    // Use get_child to find the node containing the modules, and iterate over
    // its children. If the path cannot be resolved, get_child throws.
    // A C++11 for-range loop would also work.
    BOOST_FOREACH(pt::ptree::value_type &v, tree.get_child("debug.modules")) {
        // The data function is used to access the data stored in a node.
        m_modules.insert(v.second.data());
    }

}


//[debug_settings_save
void debug_settings::save(const std::string &filename)
{
    // Create an empty property tree object.
    pt::ptree tree;

    // Put the simple values into the tree. The integer is automatically
    // converted to a string. Note that the "debug" node is automatically
    // created if it doesn't exist.
    tree.put("debug.filename", m_file);
    tree.put("debug.level", m_level);

    // Add all the modules. Unlike put, which overwrites existing nodes, add
    // adds a new node at the lowest level, so the "modules" node will have
    // multiple "module" children.
    BOOST_FOREACH(const std::string &name, m_modules)
        tree.add("debug.modules.module", name);
    storeXMLInMemory(tree);
    // Write property tree to XML file
    pt::write_xml(filename, tree);
    
}

void storeXMLInMemory(pt::ptree tree) 
{
    stringstream ss;
    pt::write_xml(ss,tree);
    string xmlDocument = ss.str();
    cout<<"Here is the XML: "<<xmlDocument<<endl;

}


void xmlTest(std::string sInputFile,std::string sOutputFile)
{
    try
    {
        debug_settings ds;
        ds.load(sInputFile);
        ds.save(sOutputFile);
        std::cout << "Success\n";
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }

}


// <read xmlns:xsd="http://www.w3.org/2001/XMLSchema" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" 
//id="76745e3d-124b-405e-af43-e4fcd3cdff72" rev="1" camera="40_1122_1_Beds5711221" 
//camera_site_id="58e333ee-69e6-4846-8346-903fdf0c5fb5" site="9b9e2e5d-9a3c-4a80-9ee3-d902f03a68ed"
// domain="66" xmlns="elsag:lprcore">

string ReadAlarmXMLMaker::deriveXmlUS(CGInfo cgi,string plate,string timeStamp,string eocGuid) 
{
    stringstream ss;

    // Create an empty property tree object.
    pt::ptree tree;

    tree.put("read", "");
    tree.put("read.<xmlattr>.id",cgi.id);
    tree.put("read.<xmlattr>.xmlns:xsd","http://www.w3.org/2001/XMLSchema");
    tree.put("read.<xmlattr>.xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    tree.put("read.<xmlattr>.rev","1");
    tree.put("read.<xmlattr>.status","5");
    tree.put("read.<xmlattr>.xmlns","elsag:lprcore");
    tree.put("read.<xmlattr>.camera",cgi.cameraName);
    tree.put("read.<xmlattr>.site",cgi.readerId);
    tree.put("read.<xmlattr>.domain",cgi.domainIdStr);

    tree.put("read.timestamp",timeStamp);
    tree.put("read.class","Invariant");
    tree.put("read.plate",plate);
    tree.put("read.confidence","0");

    //GPS section
    tree.put("read.gps.<xmlattr>.rev","0");
    tree.put("read.gps.timestamp",timeStamp);
    tree.put("read.gps.position.<xmlattr>.lat",cgi.lat);
    tree.put("read.gps.position.<xmlattr>.long",cgi.lon);
    tree.put("read.gps.position.<xmlattr>.errorradius",cgi.errorradius);
    tree.put("read.gps.velocity.<xmlattr>.east",cgi.velEast);
    tree.put("read.gps.velocity.<xmlattr>.north",cgi.velNorth);

    tree.put("read.facing","Front");
    tree.put("read.platelocation.<xmlattr>.height","578");
    tree.put("read.platelocation.<xmlattr>.width","578");
    tree.put("read.platelocation.<xmlattr>.y","578");
    tree.put("read.platelocation.<xmlattr>.x","578");

    pt::write_xml(ss,tree);


    return ss.str();
}

string ReadAlarmXMLMaker::deriveAlarmAndReadXMLUS(alarmInfo ai)
{
    stringstream ss;

    // Create an empty property tree object.
    pt::ptree tree;
    tree.put("alarm", "");
    tree.put("alarm.<xmlattr>.id",ai.alrmId);
    tree.put("alarm.<xmlattr>.rev","1");
    tree.put("alarm.<xmlattr>.status",ai.alrmStatus);
    tree.put("alarm.<xmlattr>.xmlns:xsd","http://www.w3.org/2001/XMLSchema");
    tree.put("alarm.<xmlattr>.xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    tree.put("alarm.<xmlattr>.xmlns","elsag:lpcore");

    

    tree.put("alarm.alarmtimestamp",ai.alrmTimestamp);
    tree.put("alarm.ResultText",ai.alrmResultText);
    tree.put("alarm.domain",ai.alrmDomainId);
    tree.put("alarm.read","");
    tree.put("alarm.read.<xmlattr>.id",ai.id);
    tree.put("alarm.read.<xmlattr>.xmlns:xsd","http://www.w3.org/2001/XMLSchema");
    tree.put("alarm.read.<xmlattr>.xmlns:xsi","http://www.w3.org/2001/XMLSchema-instance");
    tree.put("alarm.read.<xmlattr>.rev","1");
    tree.put("alarm.read.<xmlattr>.status","1");
    tree.put("alarm.read.<xmlattr>.xmlns","elsag:lprcore");
    tree.put("alarm.read.<xmlattr>.camera",ai.cameraName);
    tree.put("alarm.read.<xmlattr>.site",ai.readerId);
    tree.put("alarm.read.<xmlattr>.domain",ai.domainIdStr);

    tree.put("alarm.read.timestamp",ai.readTimeStamp);
    tree.put("alarm.read.class","Invariant");
    tree.put("alarm.read.plate",ai.readPlate);
    tree.put("alarm.read.confidence","0");

    //GPS section
    tree.put("alarm.read.gps.<xmlattr>.rev","0");
    tree.put("alarm.read.gps.timestamp",ai.readTimeStamp);
    tree.put("alarm.read.gps.position.<xmlattr>.lat",ai.lat);
    tree.put("alarm.read.gps.position.<xmlattr>.long",ai.lon);
    tree.put("alarm.read.gps.position.<xmlattr>.errorradius",ai.errorradius);
    tree.put("alarm.read.gps.velocity.<xmlattr>.east",ai.velEast);
    tree.put("alarm.read.gps.velocity.<xmlattr>.north",ai.velNorth);

    tree.put("alarm.read.facing","Front");
    tree.put("alarm.read.platelocation.<xmlattr>.height","578");
    tree.put("alarm.read.platelocation.<xmlattr>.width","578");
    tree.put("alarm.read.platelocation.<xmlattr>.y","578");
    tree.put("alarm.read.platelocation.<xmlattr>.x","578");

    tree.put("alarm.hotlistentry.<xmlattr>.id",ai.hotListId);
    tree.put("alarm.hotlistentry.<xmlattr>.rev",ai.hotListRev);
    tree.put("alarm.hotlistentry.<xmlattr>.ListId",ai.hotListListId);
    tree.put("alarm.hotlistentry.<xmlattr>.ListTypeId",ai.hotlistListTypeId);

    tree.put("alarm.hotlistentry.DomainId",ai.alrmDomainId);
    tree.put("alarm.hotlistentry.Plate",ai.readPlate);
    tree.put("alarm.hotlistentry.AlarmClassId2",ai.alrmAlarmClassId2);
    tree.put("alarm.hotlistentry.CreateDate",ai.alrmCreateDate);
    tree.put("alarm.hotlistentry.BeginDate",ai.alrmBeginDate);
    tree.put("alarm.hotlistentry.EndDate",ai.alrmEndDate);
    tree.put("alarm.hotlistentry.Notes",ai.alrmNotes);

    pt::write_xml(ss,tree);
    return ss.str();
}

string ReadAlarmXMLMaker::generateGUID() 
{
    boost::uuids::random_generator gen;
    boost::uuids::uuid uuid = gen();

    // Convert the UUID to a string representation
    std::string uuidStr = boost::uuids::to_string(uuid);
 
    return uuidStr;
}
void ReadAlarmXMLMaker::testAlarmXML()
{
    alarmInfo ai;

    ai.alrmId = "2c6cf1c2-e234-4331-a491-ecff3ffb9c92";
  
    ai.alrmTimestamp = "2023-08-07T09:54:27-04:00";
    ai.hotListId = "b32a88e7-1dfd-427f-9cb9-569df29f600f";
    ai.hotListListId = "55a5e859-9b15-48e8-a080-00c9bfa53aeb";
    ai.hotListRev = "1";
    ai.hotlistListTypeId  = "4";
    ai.alrmStatus = "1";
    ai.alrmDomainId = 24;
    ai.alrmAlarmClassId2 = 2;
    ai.alrmCreateDate = "1/30/2023 10:44:13 AM -05:00";
    ai.alrmBeginDate = "1/30/2023 10:44:13 AM -05:00";
    ai.alrmEndDate = "1/30/2023 10:44:13 AM -05:00";
    ai.alrmNotes = "McLean Ave";
    ai.alrmResultText = "Jammer Detected";

    ai.readTimeStamp = "2023-08-07T09:54:27-04:00";
    ai.readPlate = "WAN924";
    ai.id = "1a8f4765-73f9-0ae5-0dd8-3f45e52a72a3";
    ai.readerId = "f480bf11-fe84-42d7-a0cc-cd02e53e14c5";
    ai.domainIdStr = "24";
    ai.cameraName = "48_155_304_Camera-0304";
    ai.lat = 41.55791;
    ai.lon = -72.72122;
    ai.errorradius = 15.9357481;
    ai.velEast = 0.0251652766;
    ai.velNorth = -0.03739889;

    string sRt = deriveAlarmAndReadXMLUS(ai);
    cout<<"The XML:"<<endl<<sRt<<endl;

}

void ReadAlarmXMLMaker::testHarness()
{
    CGInfo cfi;
    cfi.cameraName = "raspberrypi-02";
    cfi.domainIdStr = "jammer detection";
    cfi.id = "alkkekubfsiopad9z=";
    cfi.reader = "ettusb210";
    cfi.readerId = "ettusb210ID";
    cfi.lat = 41.55791;
    cfi.lon = -72.72122;
    cfi.errorradius = 15.9357481;
    cfi.velEast = 0.0251562766;
    cfi.velNorth = -0.03739889;
    string plate = "DWBHEMI";
    string timeStamp = "2023-08-07T09:54:27-04:00";
    string eocGuid = "absdfgqwet8c09";

    string sRt = deriveXmlUS(cfi,plate,timeStamp,eocGuid);
    cout<<"The XML:"<<endl<<sRt<<endl;


}


EOCPutTimes generatePutTimes(time_t tt)
{
    EOCPutTimes ept;

    struct tm *timeInfo;
    timeInfo = localtime(&tt);

    char currBuf[80];
    strftime(currBuf,sizeof(currBuf),"%Y-%m-%dT%H:%M:%S",timeInfo);
    ept.createTime = currBuf;

    timeInfo->tm_hour = 0;
    timeInfo->tm_mday = 1;
    timeInfo->tm_min = 0;
    timeInfo->tm_mon = 1;
    timeInfo->tm_sec = 0;
    
    char beginBuf[80];
    strftime(beginBuf,sizeof(beginBuf),"%Y-%m-%dT%H:%M:%S",timeInfo);
    ept.beginTime = beginBuf;

    timeInfo->tm_zone += 1;
    char endBuf[80];
    strftime(endBuf,sizeof(endBuf),"%Y-%m-%dT%H:%M:%S",timeInfo);
    ept.endTime = endBuf;

    return ept;
}
