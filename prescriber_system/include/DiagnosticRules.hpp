#ifndef _DIAGNOSTICRULES_H_
#define _DIAGNOSTICRULES_H_

#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

class Prescription;

class DiagnosticRules
{
private:
    std::string disease;
    Prescription* prescription;

public:
    DiagnosticRules(std::string disease, Prescription* prescription);
    ~DiagnosticRules();

    //getter
    std::string GetDisease();
    Prescription* GetPrescription();

    //setter
    void SetDisease(std::string disease);
    void SetPrescription(Prescription* prescription);
    static std::vector<DiagnosticRules*> defaultrules();
};

#endif /* _DIAGNOSTICRULES_H_ */
