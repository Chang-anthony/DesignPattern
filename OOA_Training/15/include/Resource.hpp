#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include "../include/File.hpp"

class WebServer;

class Resource : public File
{
private:
    /* data */
    WebServer* server;
public:
    Resource();
    ~Resource();
};

#endif /* _RESOURCE_H_ */
