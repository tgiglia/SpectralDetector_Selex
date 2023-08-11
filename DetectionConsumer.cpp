#include "DetectionConsumer.hpp"
#include <thread>
#include <chrono>

void DetectionConsumer::run(ConfigData cd)
{
    SingletonStack& singletonStack = SingletonStack::getInstance();
    std::chrono::seconds sleepDuration(cd.ci.secsToWait);

    do {
        
        if(!singletonStack.theStack->empty()) {
            do{
                time_t ttTmp;
                singletonStack.theStack->pop(ttTmp);
                //is the time value late enough to post a new alarm?
                if(ttTmp > lastMessageSent + cd.ci.lastAlarmSecsIgnore)
                {
                    std::cout<<"DetectionConsumer::run: We can send Alarm message for: "<<ttTmp<<std::endl;
                    lastMessageSent = ttTmp;
                }
            }while(!singletonStack.theStack->empty());
           
        }
        std::this_thread::sleep_for(sleepDuration);

    }while(true);


}