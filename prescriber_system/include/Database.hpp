#ifndef _DATABASE_H_
#define _DATABASE_H_


#include <iostream>
#include <vector>
#include <map>
#include <string>

class Patient;
class Case;

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
    static void parser(std::string file);

    //getter
    Patient* GetPatientByid(std::string id);
    std::map<std::string, Patient*> GetData();

    //setter
    void SetData(std::map<std::string, Patient*> data);
};


#endif /* _DATABASE_H_ */
