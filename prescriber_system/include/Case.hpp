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
    std::vector<std::string> symtoms;
    Prescription* prescription;
    float time;

public:
    Case(std::vector<std::string> symtoms, Prescription* Prescription, float time);
    ~Case();

    //getter
    std::vector<std::string> GetSymtoms();
    Prescription* GetPrescription();
    float GetTime();

    //setter
    void SetSymtoms(std::vector<std::string> symtoms);
    void SetPrescription(Prescription* Prescription);
    void SetTime(float time);
};

#endif /* _CASE_H_ */
