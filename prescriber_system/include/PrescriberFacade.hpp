#ifndef _PRESCRIBERFACADE_H_
#define _PRESCRIBERFACADE_H_

#include <iostream>
#include <vector>
#include <string>

class Database;
class Prescriber;

class PrescriberFacade
{
private:
    /* data */
    Database* database;
    Prescriber* prescriber;
public:
    PrescriberFacade(Database* database, Prescriber* prescriber, 
                        std::string rulepath, std::string json);
    ~PrescriberFacade();

    void diagnosis(std::string id, std::string symtoms, int saveOpt, std::string outputpath);

    //getter
    Database* GetDataBase();
    Prescriber* GetPrescriber();

    void SetDataBase(Database* database);
    void SetPrescriber(Prescriber* prescriber);
protected:
    enum SaveOpts {
        SAVE_AS_JSON = 1 << 1, // 0010
        SAVE_AS_CSV = 1 << 2   // 0100
    };
};



#endif /* _PRESCRIBERFACADE_H_ */
