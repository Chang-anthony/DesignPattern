#include <SaveJson.hpp>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <Patient.hpp>
#include <Prescription.hpp>
#include <vector>
#include <Case.hpp>
#include <json/json.h>

SaveJson::SaveJson(/* args */)
{
}

void SaveJson::save(std::string path, Patient* patient)
{
    std::filesystem::path filepath(path);
    std::filesystem::path parent = filepath.parent_path();

    if (!std::filesystem::exists(parent)) {
        std::filesystem::create_directories(parent);
    }

    std::ofstream ofs(path);
    if (!ofs.is_open()) {
        std::cerr << "Error opening file for writing: " << path << std::endl;
        return;
    }

    std::vector<Case*> cases = patient->GetCases();

    Json::Value Cases;
    for (auto Case: cases){
        /* code */
        Json::Value newCase;
        Json::Value prescription;
        prescription["name"] = Case->GetPrescription()->GetName();
        prescription["potential"] = Case->GetPrescription()->GetPotential();
        prescription["medicines"] = Case->GetPrescription()->GetMedicines();
        prescription["usage"] = Case->GetPrescription()->GetUsage();

        newCase["symtoms"] = Case->GetSymtoms();
        newCase["time"] = Case->GetTime();
        newCase["prescription"] = prescription;

        Cases["cases"].append(newCase);
    }
    
    Json::Value json;
    json["id"] = patient->GetId();
    json["name"] = patient->GetName();
    json["gender"] = patient->GetGender();
    json["age"] = patient->GetAge();
    json["height"] = patient->GetHeight();
    json["weight"] = patient->GetWeight();
    json["cases"] = Cases;

    ofs << json;
    ofs.close();
}

SaveJson::~SaveJson()
{
}