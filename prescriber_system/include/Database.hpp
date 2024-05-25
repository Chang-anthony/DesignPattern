#ifndef _DATABASE_H_
#define _DATABASE_H_


#include <iostream>
#include <vector>
#include <map>
#include <string>

class Patient;

class Database
{
private:
    /* data */
    std::map<std::string, Patient*> data;
public:
    Database(/* args */);
    ~Database();

    void AddPatient(Patient* patient);
    static void parser(std::string file);

    //getter
    std::map<std::string, Patient*> GetData();

    //setter
    void SetData(std::map<std::string, Patient*> data);
};


#endif /* _DATABASE_H_ */
