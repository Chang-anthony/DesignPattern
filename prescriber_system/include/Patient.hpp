#ifndef _PATIENT_H_
#define _PATIENT_H_

#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

class Case;

class Patient
{
private:
    /* data */
    std::string id;
    std::string name;
    std::string gender;
    int age;
    float height;
    float weight;
    std::vector<Case*> cases;

public:
    Patient(std::string id, std::string name, std::string gender, int age, float height, float weight);
    ~Patient();

    void AddCase(Case* newCase);

    //getter
    std::string GetId();
    std::string GetName();
    std::string GetGender();
    int GetAge();
    float GetHeight();
    float GetWeight();

    //setter
    void SetId(std::string id);
    void SetName(std::string name);
    void SetGender(std::string gender);
    void SetAge(int age);
    void SetHeight(float height);
    void SetWeight(float weight);
};

#endif /* _PATIENT_H_ */
