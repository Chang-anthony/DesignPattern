#include <LazyInitDatabaseProxy.hpp>
#include <RealDatabase.hpp>
#include <Employee.hpp>


LazyInitDatabaseProxy::LazyInitDatabaseProxy(std::string fileName) : Database(fileName)
{
    realDatabase = nullptr;
}

Employee* LazyInitDatabaseProxy::getEmployeeById(int id)
{
    if (!realDatabase) {
        realDatabase = new RealDatabase(fileName);
    }

    return realDatabase->getEmployeeById(id);
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
    delete realDatabase;
}