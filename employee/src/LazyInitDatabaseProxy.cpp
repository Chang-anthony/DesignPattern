#include <LazyInitDatabaseProxy.hpp>
#include <RealDatabase.hpp>
#include <Employee.hpp>
#include <fstream>
#include <sstream>


LazyInitDatabaseProxy::LazyInitDatabaseProxy(std::string fileName) : Database(fileName)
{
    realDatabase = nullptr;
}

Employee* LazyInitDatabaseProxy::getEmployeeById(int id)
{
    if (!realDatabase) {
        realDatabase = new RealDatabase(fileName);
    }

    if (id == 0) {
        return nullptr;
    }

    std::string data = realDatabase->lines[id - 1];
    //parse data
    std::istringstream ss(data);
    std::string subordinates;

    int Id = 0;
    std::string name;
    int age = 0;
    ss >> Id >> name >> age >> subordinates;

    Employee* employee = new Employee(Id, name, age);

    return employee;
}

std::vector<Employee*> LazyInitDatabaseProxy::getSubordinatesById(int id)
{
    if (!realDatabase) {
        realDatabase = new RealDatabase(fileName);
    }

    return realDatabase->getSubordinatesById(id);
}


LazyInitDatabaseProxy::~LazyInitDatabaseProxy()
{
}