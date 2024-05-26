#include <Case.hpp>
#include <Prescription.hpp>
#include "utils.h"

Case::Case(std::vector<std::string> symtoms, Prescription* Prescription, float time)
{
    SetSymtoms(symtoms);
    SetPrescription(prescription);
    SetTime(time);
}

std::vector<std::string> Case::GetSymtoms()
{
    return symtoms;
}

Prescription* Case::GetPrescription()
{
    return prescription;
}

float Case::GetTime()
{
    return time;
}

void Case::SetSymtoms(std::vector<std::string> symtoms)
{
    this->symtoms = symtoms;
}

void Case::SetPrescription(Prescription* prescription)
{
    utils::RequireNonNull(prescription);
    this->prescription = prescription;
}

void Case::SetTime(float time)
{
    this->time = time;
}

Case::~Case()
{
}
