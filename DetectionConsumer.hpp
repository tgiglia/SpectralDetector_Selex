#ifndef DETECTIONCONSUMER_HPP
#define DETECTIONCONSUMER_HPP 

#include "ConfigData.hpp"

#include "Logger.hpp"


class DetectionConsumer
{
    protected:
        time_t lastMessageSent;
    
    public:
        DetectionConsumer() {
            lastMessageSent = 0;
        }
    void run(ConfigData cd);
};






#endif