#ifndef CURSEROBSERVER_HPP
#define CURSEROBSERVER_HPP

#include "SkillObserver.hpp"

class Role; // Forward declaration
class CurserObserver : public SkillObserver {

private:

public:
    CurserObserver(Role* actor);

    void UntilDie(Role* dead) override;
};

#endif // CURSEROBSERVER_HPP
