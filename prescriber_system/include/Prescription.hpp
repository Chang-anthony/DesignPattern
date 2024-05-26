#ifndef _PRESCRIPTION_H_
#define _PRESCRIPTION_H_

#include <iostream>
#include <string>
#include <vector>
#include "utils.h"


class Prescription
{
private:
    /* data */
    std::string name;
    std::string potential;
    std::string medicines;
    std::string usage;
public:
    Prescription(std::string name, std::string potential, std::string medicines, std::string usage);
    ~Prescription();

    //getter
    std::string GetName();
    std::string GetPotential();
    std::string GetMedicines();
    std::string GetUsage();

    //setter
    void SetName(std::string name);
    void SetPotential(std::string potential);
    void SetMedicines(std::string medicines);
    void SetUsage(std::string usage); 
};

#endif /* _PRESCRIPTION_H_ */
