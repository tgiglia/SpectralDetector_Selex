#include "DetectionConsumer.hpp"
#include "ThreadSafeStack.hpp"
#include "Logger.hpp"
#include "EOCXmlMaker.hpp"
#include "RESTUtils.hpp"
#include <thread>
#include <chrono>

void DetectionConsumer::run(ConfigData cd)
{
    SingletonStack& singletonStack = SingletonStack::getInstance();
    std::chrono::seconds sleepDuration(cd.ci.secsToWait);
    SingletonBoolean sb = SingletonBoolean::getInstance();
    bool bGotImage = false;
    std::string imageBase64;
    //Read in the Image file
    try {
        std::string imageBytes = readFileToString(cd.ai.jammerjpg);
        imageBase64 = base64_encode(imageBytes);
        bGotImage = true;
        logDbgWithTime(cd.li.spectralDbg,"Successfully read in image file!");
    }catch(const std::runtime_error& e) {
        logDbgWithTime(cd.li.spectralDbg,"ERROR: could not read in image file.");
    }
    do {
        
        if(!singletonStack.theStack->empty()) {
            do{
                time_t ttTmp;
                singletonStack.theStack->pop(ttTmp);
                //is the time value late enough to post a new alarm?
                if(ttTmp > lastMessageSent + cd.ci.lastAlarmSecsIgnore)
                {
                    //std::cout<<"DetectionConsumer::run: We can send Alarm message for: "<<ttTmp<<std::endl;
                    stringstream ss;
                    ss<<"DetectionConsumer::run: We can send Alarm message for: ";
                    ss<<ttTmp<<std::endl;

                    logDbgWithTime(cd.li.notificationDbg,ss.str());
                    EOCPutTimes ept = generatePutTimes(ttTmp);
                    cd.ai.alrmTimestamp = ept.createTime;
                    cd.ai.alrmBeginDate = ept.beginTime;
                    cd.ai.alrmCreateDate = ept.beginTime;
                    cd.ai.alrmEndDate = ept.endTime;
                    cd.ai.readTimeStamp = ept.createTime;

                    ReadAlarmXMLMaker *raxm = new ReadAlarmXMLMaker();
                    cd.ai.id = raxm->generateGUID();
                    cd.ai.alrmId = raxm->generateGUID();
                    cd.ai.overviewId = raxm->generateGUID();

                    //std::string alarmXML = raxm->deriveAlarmAndReadXMLUS(cd.ai);
                    std::string alarmXML;
                    if(bGotImage) {
                        alarmXML = raxm->deriveAlarmAndReadXMLUSHotListShortWImage(cd.ai,imageBase64);    
                    }
                    else {
                        alarmXML = raxm->deriveAlarmAndReadXMLUSHotListShort(cd.ai);    
                    }
                    
                    std::string tag = "<alarm";
                    std::string trimmedXML = raxm->trimXmlHeader(alarmXML,tag);

                    
                    //logDbgWithTime(cd.li.notificationDbg,trimmedXML);

                    RESTUtils *ru = new RESTUtils();
                    bool bSendRt = ru->putAlarmWithRead(cd,trimmedXML);
                    if(!bSendRt) {
                        logDbgWithTime(cd.li.notificationDbg,"putAlarmWithRead FAILED!");
                    }
                    else {
                        logDbgWithTime(cd.li.notificationDbg,"putAlarmWithRead SUCCEEDED!");
                    }
                    delete raxm;
                    delete ru;
                    lastMessageSent = ttTmp;
                }
            }while(!singletonStack.theStack->empty());
           
        }
        else {
            //std::cout<<"DetectionConsumber::run: nothing on the stack"<<std::endl;
        }
        std::this_thread::sleep_for(sleepDuration);

    }while(sb.keepGoing->getValue());


}