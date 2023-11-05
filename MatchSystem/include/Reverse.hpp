#ifndef _REVERSE_H_
#define _REVERSE_H_

#include "../include/MatchType.hpp"

class Individual;

class Reverse : public MatchType
{
private:
    /* data */
    MatchType* reverse;
public:
    Reverse(MatchType* reverse);
    ~Reverse();

    std::vector<Individual*> Match(Individual* preson,std::set<Individual*> individuals) override;
    Individual* result(Individual* person,std::set<Individual*> individuals) override;
};

#endif /* _REVERSE_H_ */
