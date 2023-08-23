#include "RESTUtils.hpp"
#include "Logger.hpp"
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/algorithm/string.hpp>


bool RESTUtils::testRESTGet(std::string sTarget,int port) 
{
 try {
        boost::asio::io_context io_context;
        
        // Create a resolver to resolve the server hostname and port
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve("api.example.com", "http");
        
        // Create a socket and connect to the server
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);
        
        // Create an HTTP GET request
        boost::asio::streambuf request;
        std::ostream request_stream(&request);
        request_stream << "GET /api/resource HTTP/1.1\r\n";
        request_stream << "Host: api.example.com\r\n";
        request_stream << "Accept: */*\r\n";
        request_stream << "Connection: close\r\n\r\n";
        
        // Send the request
        boost::asio::write(socket, request);
        
        // Read and print the response
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);
        
        if (status_code != 200) {
            std::cout << "Response returned with status code " << status_code << std::endl;
            return false;
        }
        
        // Read the response headers, which are terminated by a blank line
        boost::asio::read_until(socket, response, "\r\n\r\n");
        
        // Output the response headers
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
            std::cout << header << std::endl;
        }
        std::cout << std::endl;
        
        // Read and output the remaining response data
        if (response.size() > 0) {
            std::cout << &response;
        }
        
    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return false;
    }
    

 return true;
}


bool RESTUtils::testRESTPost(std::string sTarget,std::string sPort,std::string sBody)
{

  try {
        boost::asio::io_context io_context;

        // Create a resolver to resolve the server hostname and port
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve(sTarget.c_str(), sPort.c_str());

        // Create a socket and connect to the server
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

       
        std::stringstream ssHeaders;
        ssHeaders<<"POST /echo HTTP/1.1\r\n";
        ssHeaders<<"Host: "<<sTarget<<":" << sPort <<"\r\n";
        ssHeaders<<"Content-Type: application/json\r\n";
        ssHeaders<<"Content-Length: "<<std::to_string(sBody.length())<<"\r\n";
        ssHeaders<< "Connection: close\r\n\r\n";
        ssHeaders<<sBody;
        // Send the request
        std::cout<<"Sending: \n"<<ssHeaders.str()<<std::endl;
        
        size_t numWrite = boost::asio::write(socket, boost::asio::buffer(ssHeaders.str()));
        std::cout<<"Wrote "<<numWrite<<" ssHeaders is: "<<ssHeaders.str().size()<<std::endl;

        // Read and print the response
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);

        if (status_code != 200) {
            std::cout << "Response returned with status code " << status_code << std::endl;
            
            return false;
        }

        // Read the response headers, which are terminated by a blank line
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Output the response headers
        std::string header;
        while (std::getline(response_stream, header) && header != "\r") {
            std::cout << header << std::endl;
        }
        std::cout << std::endl;

        // Read and output the remaining response data
        if (response.size() > 0) {
            std::cout << &response;
        }

    } catch (std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return false;
    }
 return true;
}


bool RESTUtils::putAlarmWithRead(ConfigData cd,std::string sBody)
{
  try {

        std::string sTarget = cd.ei.eocHost;
        //std::cout<<"RESTUtils::putAlarmWithRead: target: " + sTarget;
        boost::asio::io_context io_context;

        // Create a resolver to resolve the server hostname and port
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints =
            resolver.resolve(sTarget.c_str(), std::to_string(cd.ei.eocPort).c_str());

        // Create a socket and connect to the server
        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        //set up the credentials
        std::string credentials = cd.ei.eocUser + ":" + cd.ei.eocPass;
        std::string encodedCredentials = encode64(credentials);

        //std::string encode64(const std::string &val)
        std::stringstream ssHeaders;
        ssHeaders<<"PUT /alarm/"<<cd.ai.alrmId<<" HTTP/1.1\r\n";
        ssHeaders<<"Host: "<<sTarget<<":" << std::to_string(cd.ei.eocPort).c_str() <<"\r\n";
        ssHeaders<<"Authorization: Basic " <<encodedCredentials<<"\r\n";
        ssHeaders<<"Content-Type: application/json\r\n";
        ssHeaders<<"Content-Length: "<<std::to_string(sBody.length())<<"\r\n";
        ssHeaders<< "Connection: close\r\n\r\n";
        ssHeaders<<sBody;
        // Send the request
        //std::cout<<"Sending: \n"<<ssHeaders.str()<<std::endl;
        
        size_t numWrite = boost::asio::write(socket, boost::asio::buffer(ssHeaders.str()));
        //std::cout<<"Wrote "<<numWrite<<" ssHeaders is: "<<ssHeaders.str().size()<<std::endl;

        // Read and print the response
        boost::asio::streambuf response;
        boost::asio::read_until(socket, response, "\r\n");
        std::istream response_stream(&response);
        std::string http_version;
        response_stream >> http_version;
        unsigned int status_code;
        response_stream >> status_code;
        std::string status_message;
        std::getline(response_stream, status_message);

        if (status_code != 200) {
            //std::cout << "Response returned with status code " << status_code << std::endl;
            std::stringstream sError;
            sError<<"Response returned with status code " << status_code;
            logDbgWithTime(cd.li.notificationDbg,sError.str());
            return false;
        }

        // Read the response headers, which are terminated by a blank line
        boost::asio::read_until(socket, response, "\r\n\r\n");

        // Output the response headers
        std::string header;
        /*while (std::getline(response_stream, header) && header != "\r") {
            std::cout << header << std::endl;
        }*/
        //std::cout << std::endl;

        // Read and output the remaining response data
        /*if (response.size() > 0) {
            std::cout << &response;
        }*/

    } catch (std::exception& e) {
        std::stringstream sError;
        sError << "Exception: " << e.what() << std::endl;
        logDbgWithTime(cd.li.notificationDbg,sError.str());
        return false;
    }


    return true;
}


std::string RESTUtils::decode64(const std::string &val) {
    using namespace boost::archive::iterators;
    using It = transform_width<binary_from_base64<std::string::const_iterator>, 8, 6>;
    return boost::algorithm::trim_right_copy_if(std::string(It(std::begin(val)), It(std::end(val))), [](char c) {
        return c == '\0';
    });
}

std::string RESTUtils::encode64(const std::string &val) {
    using namespace boost::archive::iterators;
    using It = base64_from_binary<transform_width<std::string::const_iterator, 6, 8>>;
    auto tmp = std::string(It(std::begin(val)), It(std::end(val)));
    return tmp.append((3 - val.size() % 3) % 3, '=');
}

