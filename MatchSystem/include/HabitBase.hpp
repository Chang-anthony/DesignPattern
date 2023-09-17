#ifndef _HABITBASE_H_
#define _HABITBASE_H_

#include "../include/MatchType.hpp"

class HabitBase : public MatchType
{
private:
    /* data */
public:
    HabitBase(/* args */);
    ~HabitBase();
    
    Individual* Match(Individual* preson,std::set<Individual*> individuals) override;
};

#endif /* _HABITBASE_H_ */
