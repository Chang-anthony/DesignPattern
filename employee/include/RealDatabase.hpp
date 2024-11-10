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
protected:
    Employee* readDataByid(int id);
};


#endif /* _REALDATABASE_H_ */
