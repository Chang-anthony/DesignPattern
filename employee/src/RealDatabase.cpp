#include <Employee.hpp>
#include <RealDatabase.hpp>
#include <fstream>
#include <sstream>

RealDatabase::RealDatabase(std::string fileName) : Database(fileName)
{
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }

}

Employee* RealDatabase::getEmployeeById(int id)
{
    return readDataByid(id);
}

std::vector<Employee*> RealDatabase::getSubordinatesById(int id)
{
    Employee* employee = readDataByid(id);
    if (employee == nullptr) {
        return std::vector<Employee*>();
    }
    std::string data = lines[id];
    //parse data
    std::istringstream ss(data);
    std::string subordinates;

    int Id = 0;
    std::string name;
    int age = 0;
    ss >> Id >> name >> age >> subordinates;
    return readSubordinates(lines, subordinates);
}

Employee* RealDatabase::readDataByid(int id)
{
    if (id == 0) {
        return nullptr;
    }

    if ((lines.size() - 1) < id) {
        return nullptr;
    } 
    std::string data = lines[id];
    //parse data
    std::istringstream ss(data);
    std::string subordinates;

    int Id = 0;
    std::string name;
    int age = 0;
    ss >> Id >> name >> age >> subordinates;

    //parser subordinates
    std::vector<Employee*> subordinatesList = readSubordinates(lines, subordinates);
    Employee* employee = new Employee(Id, name, age, subordinatesList);

    return employee;
}

std::vector<Employee*> RealDatabase::readSubordinates(std::vector<std::string> datas, std::string subordinates)
{
    std::vector<int> subordinatesId;
    std::istringstream ssSubordinates(subordinates);
    std::string subId;
    while (std::getline(ssSubordinates, subId, ',')) {
        subordinatesId.push_back(std::stoi(subId));
    }

    std::vector<Employee*> subordinate;
    for (int i = 0; i < subordinatesId.size(); i++) {
        int id = subordinatesId[i];
        std::string data = datas[id];

        //parse data
        std::istringstream ss(data);
        std::string sub;
        int Id = 0;
        std::string name;
        int age = 0;
        ss >> Id >> name >> age >> sub;

        std::vector<Employee*> employees = readSubordinates(datas, sub);
        Employee* employee = new Employee(Id, name, age, employees);
        subordinate.push_back(employee);
    }
    return subordinate;
}


RealDatabase::~RealDatabase()
{

}


