#ifndef _LAZYINITDATABASEPROXY_H_
#define _LAZYINITDATABASEPROXY_H_

#include <iostream>
#include <string>
#include <Database.hpp>

class Employee;
class RealDatabase;

class LazyInitDatabaseProxy : public Database
{
private:
    /* data */
public:
    LazyInitDatabaseProxy(std::string fileName);
    ~LazyInitDatabaseProxy();

    Employee* getEmployeeById(int id) override;
    std::vector<Employee*> getSubordinatesById(int id) override;

protected:
    RealDatabase* realDatabase;
    friend class RealDatabase;
};

#endif /* _LAZYINITDATABASEPROXY_H_ */
