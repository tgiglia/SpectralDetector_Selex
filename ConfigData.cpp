#include "ConfigData.hpp"
#include "Logger.hpp"



bool ConfigData::loadConfig(string sXmlPath,string dbgFile)
{
    // Create empty property tree object
    pt::ptree tree;
    // Parse the XML into the property tree.
    pt::read_xml(sXmlPath, tree);
    try {
        ai.readerId = tree.get<std::string>("configuration.alarminfo.readerId");
        ai.readPlate = tree.get<std::string>("configuration.alarminfo.readPlate");
        ai.domainIdStr = tree.get<std::string>("configuration.alarminfo.domainIdStr");
        ai.cameraName = tree.get<std::string>("configuration.alarminfo.cameraName");
        ai.hotListId = tree.get<std::string>("configuration.alarminfo.hotListId");
        ai.hotListListId = tree.get<std::string>("configuration.alarminfo.hotListListId");
        ai.hotListRev = tree.get<std::string>("configuration.alarminfo.hotListRev");
        ai.hotlistListTypeId = tree.get<std::string>("configuration.alarminfo.hotlistListTypeId");
        ai.alrmStatus = tree.get<std::string>("configuration.alarminfo.alrmStatus");
        ai.alrmDomainId = tree.get<int>("configuration.alarminfo.alrmDomainId");
        ai.alrmAlarmClassId2 = tree.get<int>("configuration.alarminfo.alrmAlarmClassId2");
        ai.alrmNotes = tree.get<std::string>("configuration.alarminfo.alrmNotes");
        ai.alrmResultText = tree.get<std::string>("configuration.alarminfo.alrmResultText");
        ai.lat = tree.get<double>("configuration.alarminfo.lat");
        ai.lon = tree.get<double>("configuration.alarminfo.lon");
        ai.errorradius = tree.get<double>("configuration.alarminfo.errorradius");
        ai.velEast = tree.get<double>("configuration.alarminfo.velEast");
        ai.velNorth = tree.get<double>("configuration.alarminfo.velNorth");
        ci.secsToWait = tree.get<int>("configuration.consumer.secsToWait");
        ci.lastAlarmSecsIgnore = tree.get<int>("configuration.consumer.lastAlarmSecsIgnore");
        li.jammerDbg = tree.get<std::string>("configuration.logging.jammerDbg");
        li.notificationDbg = tree.get<std::string>("configuration.logging.notificationDbg");
        li.spectralDbg = tree.get<std::string>("configuration.logging.spectralDbg");

    }catch(std::exception ex) {
        cout<<"ConfigData::load: ERROR: "<<ex.what()<<endl;
        logDbgWithTime(dbgFile,ex.what());

    }
    return true;
}

string ConfigData::showConfig()
{
    stringstream ss;
    ss<<"readerId: ";
    if(ai.readerId.size() > 0) {
        ss<<ai.readerId<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"readPlate: ";
    if(ai.readPlate.size() > 0) {
        ss<<ai.readPlate<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"domainIdStr: ";
    if(ai.domainIdStr.size() > 0) {
        ss<<ai.domainIdStr<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"cameraName: ";
    if(ai.cameraName.size() > 0) {
        ss<<ai.cameraName<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"hotListId: ";
    if(ai.hotListId.size() > 0) {
        ss<<ai.hotListId<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"hotListListId: ";
    if(ai.hotListListId.size() > 0) {
        ss<<ai.hotListListId<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"hotListRev: ";
    if(ai.hotListRev.size() > 0) {
        ss<<ai.hotListRev<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"hotlistListTypeId: ";
    if(ai.hotlistListTypeId.size() > 0) {
        ss<<ai.hotlistListTypeId<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"alrmStatus: ";
    if(ai.alrmStatus.size() > 0) {
        ss<<ai.alrmStatus<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"alrmDomainId: "<<ai.alrmDomainId<<endl;
    ss<<"alrmAlarmClassId2: "<<ai.alrmAlarmClassId2<<endl;
    ss<<"alrmNotes: ";
    if(ai.alrmNotes.size() > 0) {
        ss<<ai.alrmNotes<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"alrmResultText: ";
    if(ai.alrmResultText.size() > 0) {
        ss<<ai.alrmResultText<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"lat: "<<ai.lat<<endl;
    ss<<"lon: "<<ai.lon<<endl;
    ss<<"errorradius: "<<ai.errorradius<<endl;
    ss<<"velEast: "<<ai.velEast<<endl;
    ss<<"velNorth: "<<ai.velNorth<<endl;
    ss<<"secsToWait: "<<ci.secsToWait<<endl;
    ss<<"lastAlarmSecsIgnore: "<<ci.lastAlarmSecsIgnore<<endl;
    ss<<"jammerDbg: ";
    if(li.jammerDbg.size() > 0) {
        ss<<li.jammerDbg<<endl;
    }
    else {
        ss<<"No value"<<endl;
    }
    ss<<"notificationDbg: ";
    if(li.notificationDbg.size() > 0) {
        ss<<li.notificationDbg<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }
    ss<<"spectralDbg: ";
    if(li.spectralDbg.size() > 0) {
        ss<<li.spectralDbg<<endl;
    }
    else {
        ss<<"No Value"<<endl;
    }

    return ss.str();
}