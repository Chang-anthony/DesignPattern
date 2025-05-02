#ifndef CURSEROBSERVER_HPP
#define CURSEROBSERVER_HPP

#include "SkillObserver.hpp"

class Role; // Forward declaration
class CurserObserver : public SkillObserver {

private:

public:
    CurserObserver(Role* actor);

    void UntilDie() override;
};

#endif // CURSEROBSERVER_HPP
