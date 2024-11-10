#ifndef _PASSWORDPROTECTPROXY_H_
#define _PASSWORDPROTECTPROXY_H_

#include <iostream>
#include <string>
#include <LazyInitDatabaseProxy.hpp>

class PasswordProtectProxy : public LazyInitDatabaseProxy
{
private:
    /* data */
public:
    PasswordProtectProxy(std::string fileName);
    ~PasswordProtectProxy();

    Employee* getEmployeeById(int id) override;
    std::vector<Employee*> getSubordinatesById(int id) override;
protected:
    bool authenticate();
};


#endif /* _PASSWORDPROTECTPROXY_H_ */
