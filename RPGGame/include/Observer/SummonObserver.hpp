#ifndef _SUMMONOBSERVER_H_
#define _SUMMONOBSERVER_H_

#include "SkillObserver.hpp"

class SummonObserver : public SkillObserver {
public:
    void UntilDie() override;
};

#endif /* _SUMMONOBSERVER_H_ */
