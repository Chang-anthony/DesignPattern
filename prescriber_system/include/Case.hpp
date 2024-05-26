#ifndef _CASE_H_
#define _CASE_H_

#include <iostream>
#include <string>
#include <vector>

class Prescription;

class Case
{
private:
    /* data */
    std::string symtoms;
    Prescription* prescription;
    float time;

public:
    Case(std::string symtoms, Prescription* Prescription, float time);
    ~Case();

    //getter
    std::string GetSymtoms();
    Prescription* GetPrescription();
    float GetTime();

    //setter
    void SetSymtoms(std::string symtoms);
    void SetPrescription(Prescription* Prescription);
    void SetTime(float time);
};

#endif /* _CASE_H_ */
