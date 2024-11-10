#include <PasswordProtectProxy.hpp>
#include <cstdlib>

PasswordProtectProxy::PasswordProtectProxy(std::string fileName) : LazyInitDatabaseProxy(fileName)
{
    
}

Employee* PasswordProtectProxy::getEmployeeById(int id)
{
    if (authenticate()) {
        return LazyInitDatabaseProxy::getEmployeeById(id);
    }
    return nullptr;
}

std::vector<Employee*> PasswordProtectProxy::getSubordinatesById(int id)
{
    if (authenticate()) {
        return LazyInitDatabaseProxy::getSubordinatesById(id);
    }
    return std::vector<Employee*>();
}

bool PasswordProtectProxy::authenticate()
{
    const char* password = std::getenv("PASSWORD");

    return password != nullptr && std::string(password) == "1qaz2wsx";
}

PasswordProtectProxy::~PasswordProtectProxy()
{
}