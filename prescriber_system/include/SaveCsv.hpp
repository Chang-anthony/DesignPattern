#ifndef _SAVECSV_H_
#define _SAVECSV_H_

#include <SaveDiagnositic.hpp>

class SaveCsv : public SaveDiagnositic
{
private:
    /* data */
public:
    SaveCsv(/* args */);
    ~SaveCsv();

    void save(std::string path, std::string id, std::string symptom) override;
};

#endif /* _SAVECSV_H_ */
