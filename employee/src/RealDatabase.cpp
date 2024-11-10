#include <Employee.hpp>
#include <RealDatabase.hpp>

RealDatabase::RealDatabase(std::string fileName) : Database(fileName)
{
    
}

Employee* RealDatabase::getEmployeeById(int id)
{
    return readDataByid(id);
}

Employee* RealDatabase::readDataByid(int id)
{
    //TODO: Read data from file
    

}


RealDatabase::~RealDatabase()
{

}


