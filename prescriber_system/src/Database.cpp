#include <Database.hpp>
#include <Patient.hpp>
#include "utils.h"

Database::Database(/* args */)
{
    data = std::map<std::string, Patient*>();
}

void Database::AddPatient(Patient* patient)
{
    utils::RequireNonNull(patient);
    data.insert({patient->GetId(), patient});
}

//TODO
void Database::parser(std::string file)
{

}

std::map<std::string, Patient*> Database::GetData()
{
    return data;
}


void Database::SetData(std::map<std::string, Patient*> data)
{
    this->data = data;
}

Database::~Database()
{
}