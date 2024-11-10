#include <Employee.hpp>
#include <RealDatabase.hpp>
#include <fstream>
#include <sstream>

RealDatabase::RealDatabase(std::string fileName) : Database(fileName)
{
    
}

Employee* RealDatabase::getEmployeeById(int id)
{
    return readDataByid(id);
}

Employee* RealDatabase::readDataByid(int id)
{
    if (id == 0) {
        return nullptr;
    }
    std::vector<std::string> lines;
    std::ifstream file(fileName);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }

    if ((lines.size() - 1) < id) {
        return nullptr;
    } 
    std::string data = lines[id - 1];
    //parse data
    std::istringstream ss(data);
    std::string subordinates;

    int id = 0;
    std::string name;
    int age = 0;
    std::vector<int> subordinatesId;
    ss >> id >> name >> age >> subordinates;

    //parser subordinates
    std::istringstream ssSubordinates(subordinates);
    std::string subId;
    while (std::getline(ssSubordinates, subId, ',')) {
        subordinatesId.push_back(std::stoi(subId));
    }
    std::vector<Employee*> subordinatesList = readSubordinates(lines, subordinatesId);
    Employee* employee = new Employee(id, name, age, subordinatesList);

    return employee;
}

std::vector<Employee*> RealDatabase::readSubordinates(std::vector<std::string> datas, std::vector<int> subordinatesId)
{
    std::vector<Employee*> subordinates;
    for (int i = 0; i < subordinatesId.size(); i++) {
        int id = subordinatesId[i];
        Employee* employee = readDataByid(id);
        if (employee != nullptr) {
            subordinates.push_back(employee);
        }
    }
    return subordinates;
}


RealDatabase::~RealDatabase()
{

}


