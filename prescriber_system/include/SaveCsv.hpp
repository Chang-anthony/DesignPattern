#ifndef _SAVECSV_H_
#define _SAVECSV_H_

#include <SaveDiagnositic.hpp>

class Patient;

class SaveCsv : public SaveDiagnositic
{
private:
    /* data */
public:
    SaveCsv(/* args */);
    ~SaveCsv();

    void save(std::string path, Patient* patient) override;
protected:
};

#endif /* _SAVECSV_H_ */
