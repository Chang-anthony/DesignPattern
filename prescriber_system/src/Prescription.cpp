#include <Prescription.hpp>


Prescription::Prescription()
{
}

Prescription::Prescription(std::string name, std::string potential, std::string medicines, std::string usage)
{
    SetName(name);
    SetPotential(potential);
    SetMedicines(medicines);
    SetUsage(usage);
}

std::string Prescription::GetName()
{
    return name;
}

std::string Prescription::GetPotential()
{
    return potential;
}

std::string Prescription::GetMedicines()
{
    return medicines;
}

std::string Prescription::GetUsage()
{
    return usage;
}

void Prescription::SetName(std::string name)
{
    utils::LengthShouldBe(name, 4, 30);
    this->name = name;
}

void Prescription::SetPotential(std::string potential)
{
    utils::LengthShouldBe(potential, 3, 100);
    this->potential = potential;
}

void Prescription::SetMedicines(std::string medicines)
{
    utils::LengthShouldBe(medicines, 3, 30);
    this->medicines = medicines;
}

void Prescription::SetUsage(std::string usage)
{
    utils::LengthShouldBe(usage, 0, 1000);
    this->usage = usage;
}


Prescription::~Prescription()
{
}