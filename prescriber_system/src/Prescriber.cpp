#include <Prescriber.hpp>
#include <Database.hpp>
#include <DiagnosticRules.hpp>
#include <Case.hpp>
#include <FileIterator.hpp>
#include <SaveDiagnositic.hpp>
#include <Prescription.hpp>
#include <Patient.hpp>
#include <chrono>
#include <thread>


Prescriber::Prescriber(Database* database, SaveDiagnositic* strategy)
{
    SetDataBase(database);
    this->demands = std::vector<std::pair<std::string,std::string>>();
    this->rules = DiagnosticRules::defaultrules();
}

//TODO
void Prescriber::diagnosis(std::string id, std::string symptom)
{
    Patient* patient = database->GetPatientByid(id);
    if (patient) {
        auto start = std::chrono::high_resolution_clock::now();
        Prescription* prescription = this->dodiagnosis(symptom, patient);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        if (prescription) {
            patient->AddCase(new Case(symptom, prescription, duration.count()));
        }
    }
}

Prescription* Prescriber::dodiagnosis(std::string symptom, Patient* patient)
{
    Prescription* prescription = nullptr;
    for (auto rule: this->rules) {
        if(symptom == rule->GetDisease()) {
            prescription = rule->GetPrescription();
            break;
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));

    return prescription;
}

void Prescriber::save(std::string path, std::string id)
{
    strategy->save(path, id);
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

SaveDiagnositic* Prescriber::GetStrategy()
{
    return strategy;
}

void Prescriber::SetDataBase(Database* database)
{
    utils::RequireNonNull(database);
    this->database = database;
}

void Prescriber::SetStrategy(SaveDiagnositic* strategy)
{
    utils::RequireNonNull(strategy);
    this->strategy = strategy;
}

Prescriber::~Prescriber()
{
}