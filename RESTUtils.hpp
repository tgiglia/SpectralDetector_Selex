#ifndef REST_UTILIS_HPP
#define REST_UTILS_HPP 

#include <boost/asio.hpp>
#include <iostream>
#include <string>

class RESTUtils {

 public:
  bool testRESTGet(std::string sTarget,int port);
  bool testRESTPost(std::string sTarget,std::string sPort,std::string sBody);



};




#endif


