#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <iostream>
#include <set>
#include <string>

class Response;
class Resource;

class WebServer
{
private:
    /* data */
    Resource* resource;
public:
    WebServer(/* args */);
    ~WebServer();

    Response* Request(std::string url);
};


#endif /* _WEBSERVER_H_ */
