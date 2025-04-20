#ifndef CURSEROBSERVER_HPP
#define CURSEROBSERVER_HPP

#include "SkillObserver.hpp"

class CurserObserver : public SkillObserver {
public:
    void UntilDie() override;
};

#endif // CURSEROBSERVER_HPP
