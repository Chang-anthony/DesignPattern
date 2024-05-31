#ifndef _DATABASE_H_
#define _DATABASE_H_


#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <json/json.h>

class Patient;
class Case;
class Prescription;

class Database
{
private:
    /* data */
    std::map<std::string, Patient*> data;
public:
    Database(/* args */);
    ~Database();

    void AddCaseById(std::string id, Case* newCase);
    void AddPatient(Patient* patient);
    void parser(std::string json);

    //getter
    Patient* GetPatientByid(std::string id);
    std::map<std::string, Patient*> GetData();

    //setter
    void SetData(std::map<std::string, Patient*> data);

protected:
    void JsonParser(const Json::Value& person);
    std::vector<Case*> ParserCase(const Json::Value& Cases);
};


#endif /* _DATABASE_H_ */
