#ifndef _SAVEDIAGNOSITIC_H_
#define _SAVEDIAGNOSITIC_H_

#include <iostream>
#include <vector>
#include <string>

class SaveDiagnositic
{
private:
    /* data */
public:
    SaveDiagnositic(/* args */);
    ~SaveDiagnositic();

    virtual void save(std::string path, std::string id, std::string symptom) = 0;
};

#endif /* _SAVEDIAGNOSITIC_H_ */
