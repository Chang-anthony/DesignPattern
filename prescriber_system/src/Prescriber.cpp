#include <Prescriber.hpp>
#include <Database.hpp>
#include <DiagnosticRules.hpp>
#include <Case.hpp>


Prescriber::Prescriber(Database* database)
{
    SetDataBase(database);
    this->demands = std::vector<std::pair<std::string,std::string>>();
    this->rules = DiagnosticRules::defaultrules();
}


void Prescriber::AddDemand(std::string id, std::string symptom)
{
    std::pair<std::string,std::string> demand(id, symptom);
    this->demands.push_back(demand);
}

void Prescriber::AddRule(DiagnosticRules* rule)
{
    utils::RequireNonNull(rule);
    this->rules.push_back(rule);
}

//TODO
void Prescriber::parser(std::string file)
{
    
}

void Prescriber::store(std::string id, Case* newCase)
{   
    utils::RequireNonNull(newCase);
    this->database->AddCaseById(id, newCase);
}

Database* Prescriber::GetDataBase()
{
    return database;
}

void Prescriber::SetDataBase(Database* database)
{
    utils::RequireNonNull(database);
    this->database = database;
}


Prescriber::~Prescriber()
{
}