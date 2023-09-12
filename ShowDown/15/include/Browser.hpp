#ifndef _BROWSER_H_
#define _BROWSER_H_

#include <iostream>
#include <vector>
#include <string>

class WebServer;
class File;
class Browser
{
private:
    /* data */
public:
    Browser();
    ~Browser();

    void SendRequest(WebServer* server,std::string url);

    void Render(File* file);
};

#endif /* _BROWSER_H_ */
