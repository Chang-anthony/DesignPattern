#include <Database.hpp>
#include <Patient.hpp>
#include <Prescription.hpp>
#include <Case.hpp>
#include <json/json.h>
#include <fstream>
#include "utils.h"

Database::Database(/* args */)
{
    data = std::map<std::string, Patient*>();
}

Patient* Database::GetPatientByid(std::string id)
{
    if(data.find(id) != data.end())
        return data[id];
    return nullptr;
}

void Database::AddCaseById(std::string id, Case* newCase)
{
    if(data.find(id) != data.end())
        data[id]->AddCase(newCase);
}

void Database::AddPatient(Patient* patient)
{
    utils::RequireNonNull(patient);
    data.insert({patient->GetId(), patient});
}

void Database::JsonParser(const Json::Value& person) 
{
    std::string id;
    std::string name;
    std::string gender;
    int age;
    float height;
    float weight;
    std::vector<Case*> cases = std::vector<Case*>();

    bool flag = person.isMember("id") && person.isMember("name") && 
                person.isMember("gender") && person.isMember("age") &&
                person.isMember("height") && person.isMember("weight") &&
                person.isMember("case");
    
    if (flag) {
        id = person["id"].asString();
        name = person["name"].asString();
        gender = person["gender"].asString();
        age = person["age"].asInt();
        height = person["height"].asFloat();
        weight = person["weight"].asFloat();
        cases = ParserCase(person);
        Patient* patient = new Patient(id, name, gender, age, height, weight);
        patient->SetCases(cases);
        data.insert({id, patient});
    }
}

std::vector<Case*> Database::ParserCase(const Json::Value& Cases) 
{
    std::vector<Case*> cases = std::vector<Case*>();
    for (const auto& c: Cases["case"]) {
        std::string symtom;
        float time;
        Prescription* prescript = new Prescription();

        bool flag = c.isMember("symtoms") && c.isMember("time") && c.isMember("prescription");

        if (flag) {
            symtom = c["symtoms"].asString();
            time = c["time"].asFloat();
        }
        else
            continue;
            
        bool check = false;
        for (const auto& prescription : c["prescription"]) {
            check = prescription.isMember("name") && 
                    prescription.isMember("potential") && 
                    prescription.isMember("medicines") && 
                    prescription.isMember("usage");
            if (check) {
                prescript->SetName(prescription["name"].asString());
                prescript->SetPotential(prescription["potential"].asString());
                prescript->SetMedicines(prescription["medicines"].asString());
                prescript->SetUsage(prescription["usage"].asString());
            }
            else
                continue;
        }
        cases.push_back(new Case(symtom, prescript, time));
    }
    return cases;
}

void Database::parser(std::string json)
{
    std::ifstream ifs(json);
    if(!ifs.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    Json::Value root;
    Json::CharReaderBuilder readerBulider;
    std::string errs;

    if (!Json::parseFromStream(readerBulider, ifs, &root, &errs)) {
        std::cerr << "Error parsing JSON: " << errs << std::endl;
        return ;
    }

    if(root.isMember("persons") && root["persons"].isArray()) {
        const Json::Value& persons = root["persons"];
        for (const auto& person : persons) {
            this->JsonParser(person);
        }
    }
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