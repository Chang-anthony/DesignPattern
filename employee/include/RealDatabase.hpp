#ifndef _REALDATABASE_H_
#define _REALDATABASE_H_

#include <iostream>
#include <string>
#include <vector>
#include <Database.hpp>
#include <map>

class Employee;

class RealDatabase : public Database
{
private:
    /* data */
public:
    RealDatabase(std::string fileName);
    ~RealDatabase();

    Employee* getEmployeeById(int id) override;
    std::vector<Employee*> getSubordinatesById(int id) override;

protected:
    std::vector<std::string> lines;
    Employee* readDataByid(int id);
    std::vector<Employee*> readSubordinates(std::vector<std::string> datas, std::string subordinates);
    friend class LazyInitDatabaseProxy;
};


#endif /* _REALDATABASE_H_ */
