#include <Prescriber.hpp>
#include <Database.hpp>
#include <DiagnosticRules.hpp>
#include <Case.hpp>
#include <FileIterator.hpp>


Prescriber::Prescriber(Database* database)
{
    SetDataBase(database);
    this->demands = std::vector<std::pair<std::string,std::string>>();
    this->rules = DiagnosticRules::defaultrules();
}

//TODO
void Prescriber::diagnosis(std::string id, std::string symptom)
{

}

void Prescriber::save(std::string path, std::string id, std::string symptom)
{
    
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

void Prescriber::parser(std::string file)
{
    FileIterator it = FileIterator(file);
    while (!it) {
        this->rules.push_back(DiagnosticRules::GenRule(*it));
        ++it;
    }
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