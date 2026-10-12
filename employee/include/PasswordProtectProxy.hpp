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
    // 直接給定密碼（不讀環境變數 PASSWORD），方便測試
    PasswordProtectProxy(std::string fileName, std::string password);
    ~PasswordProtectProxy();

    Employee* getEmployeeById(int id) override;
    std::vector<Employee*> getSubordinatesById(int id) override;
protected:
    bool authenticate();
    bool hasGivenPassword;
    std::string givenPassword;
};


#endif /* _PASSWORDPROTECTPROXY_H_ */
