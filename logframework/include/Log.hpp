#ifndef _LOG_H_
#define _LOG_H_


#include <iostream>
#include <string>
#include <vector>
#include <Logger.hpp>

class Log : public Logger
{
private:
    /* data */
public:
    Log(std::string name, Level level, Layout* layout, Exporter* exporter);
    Log(Log* parent, std::string name, Level level, Layout* layout, Exporter* exporter);
    ~Log();

    Logger* GetLog(std::string name);

    //getters
    std::vector<Logger*> GetChild();

    //setters
    void SetChild(std::vector<Logger*> child);
protected:
    std::vector<Logger*> child;
};



#endif /* _LOG_H_ */
