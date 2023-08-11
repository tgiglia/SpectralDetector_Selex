#ifndef NOTIFY_INFO_HPP
#define NOTIFY_INFO_HPP 

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <fstream>

#include <chrono>
#include <ctime>



class NotifyInfo
{
 public:
  std::string sNotifyFile;
  std::string sNotifyHost;
  std::string sMessage;
  int iPort;	
	
	
};

class NotifyBase
{
	public:
		virtual bool sendNotify(NotifyInfo ni) = 0;
};


class FileNotify : public NotifyBase
{
	public:
		virtual bool sendNotify(NotifyInfo ni);
		
	protected:
		bool logIt(std::string sFileName,std::string message);
	
};


#endif

