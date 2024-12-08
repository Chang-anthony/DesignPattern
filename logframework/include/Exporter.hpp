#ifndef _EXPORTER_H_
#define _EXPORTER_H_

#include <iostream>
#include <string>

class Logger;

class Exporter
{
private:
    /* data */
public:
    Exporter();
    ~Exporter();

    virtual void output(std::string message) = 0;

    void SetLogger(Logger* logger);
    Logger* GetLogger();

protected:
    Logger* logger;
};




#endif /* _EXPORTER_H_ */
