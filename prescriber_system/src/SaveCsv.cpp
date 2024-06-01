#include <SaveCsv.hpp>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <Patient.hpp>
#include <Prescription.hpp>
#include <vector>
#include <Case.hpp>

SaveCsv::SaveCsv(/* args */)
{
}

void SaveCsv::save(std::string path, Patient* patient) 
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
    

    Case* lastCase = patient->GetCases()[patient->GetCases().size() - 1];
    Prescription* prescription = lastCase->GetPrescription();

    //write csv header
    ofs << "id,name,gender,age,height,weight,case" << std::endl;

    ofs << patient->GetId() << ","
        << patient->GetName() << ","
        << patient->GetGender() << ","
        << std::to_string(patient->GetAge()) << ","
        << std::to_string(patient->GetHeight()) << ","
        << std::to_string(patient->GetWeight()) << ","
        << "\"" << "symtoms: " << lastCase->GetSymtoms() << ","
                << "time: " << lastCase->GetTime() << ","
            << "\"" << "prescription: "
                << "name: " << prescription->GetName() << ","
                << "potential" << prescription->GetPotential() << ","
                << "medicines" << prescription->GetMedicines() << ","
                << "usage" << prescription->GetUsage()
            << "\""
        << "\"" << std::endl;
    
    ofs.close();
}

SaveCsv::~SaveCsv()
{
}