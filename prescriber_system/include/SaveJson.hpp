#ifndef _SAVEJSON_H_
#define _SAVEJSON_H_


#include <SaveDiagnositic.hpp>
class Patient;

class SaveJson : public SaveDiagnositic
{
private:
    /* data */
public:
    SaveJson(/* args */);
    ~SaveJson();

    void save(std::string path, Patient* id) override;
};

#endif /* _SAVEJSON_H_ */
