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

class Prescriber
{
private:
    /* data */
    std::vector<std::pair<std::string,std::string>> demands;
    std::vector<DiagnosticRules*> rules;
    Database* database;

public:
    Prescriber(Database* database);
    ~Prescriber();

    void AddDemand(std::string id, std::string symptom);
    void AddRule(DiagnosticRules* rule);

    void diagnosis(std::string id, std::string symptom);
    void parser(std::string file);
    void save(std::string path, std::string id, std::string symptom);
    void store(std::string id, Case* newCase);

    //getter
    Database* GetDataBase();

    //setter
    void SetDataBase(Database* database);

protected:
    
};


#endif /* _PRESCRIBER_H_ */
