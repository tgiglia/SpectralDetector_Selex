#ifndef REST_UTILIS_HPP
#define REST_UTILS_HPP 

#include "ConfigData.hpp"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <string>

class RESTUtils {

 public:
  bool testRESTGet(std::string sTarget,int port);
  bool testRESTPost(std::string sTarget,std::string sPort,std::string sBody);
  bool putAlarmWithRead(ConfigData cd,std::string sBody);
  bool putAlarmWithReadBeast(ConfigData cd,string sBody);
  std::string decode64(const std::string &val);
  std::string encode64(const std::string &val);

};




#endif


