#ifndef _STANDARDLAYOUT_H_
#define _STANDARDLAYOUT_H_

#include <iostream>
#include <Layout.hpp>

class Logger;

class StandardLayout : public Layout
{
private:
    /* data */
public:
    StandardLayout();
    ~StandardLayout();

    std::string format(std::string message) override;

protected:
    std::string GetCurrentTime();
};


#endif /* _STANDARDLAYOUT_H_ */
