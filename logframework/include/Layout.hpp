#ifndef _LAYOUT_H_
#define _LAYOUT_H_

#include <iostream>
#include <string>
#include <vector>

class Logger;

class Layout
{
private:
    /* data */
public:
    Layout();
    ~Layout();

    virtual std::string format(std::string message) = 0;

    Logger* GetLogger();
    void SetLogger(Logger* logger);

protected:
    Logger *logger;
};

#endif /* _LAYOUT_H_ */
