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
public:
    Database(std::string fileName);
    ~Database();

    virtual Employee* getEmployeeById(int id) = 0;

protected:
    std::string fileName;
};


#endif /* _DATABASE_H_ */
