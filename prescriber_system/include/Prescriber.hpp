#ifndef _PRESCRIBER_H_
#define _PRESCRIBER_H_

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "utils.h"

class DiagnosticRules;
class Case;
class Database;
class SaveDiagnositic;
class Prescription;
class Patient;

class Prescriber
{
private:
    /* data */
    std::vector<std::pair<std::string,std::string>> demands;
    std::vector<DiagnosticRules*> rules;
    Database* database;
    SaveDiagnositic* strategy;

public:
    Prescriber(Database* database, SaveDiagnositic* strategy);
    ~Prescriber();

    void AddDemand(std::string id, std::string symptom);
    void AddRule(DiagnosticRules* rule);

    void diagnosis(std::string id, std::string symptom);
    void parser(std::string file);
    void save(std::string path, std::string id);
    void store(std::string id, Case* newCase);

    //getter
    Database* GetDataBase();
    SaveDiagnositic* GetStrategy();

    //setter
    void SetDataBase(Database* database);
    void SetStrategy(SaveDiagnositic* strategy);

protected:
    Prescription* dodiagnosis(std::string symptom, Patient* patient);

};


#endif /* _PRESCRIBER_H_ */
