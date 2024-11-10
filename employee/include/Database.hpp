#ifndef _DATABASE_H_
#define _DATABASE_H_


#include <iostream>
#include <string>
#include <vector>

class Employee;

class Database
{
private:
    /* data */
    std::string fileName;
public:
    Database(std::string fileName);
    ~Database();

    virtual Employee* getEmployeeById(int id) = 0;
};


#endif /* _DATABASE_H_ */
