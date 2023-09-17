#ifndef _MATCHTYPE_H_
#define _MATCHTYPE_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>

class Individual;

class MatchType
{
private:
    /* data */
public:
    MatchType();
    ~MatchType();

    virtual Individual* Match(Individual* person,std::set<Individual*> individuals) = 0;
};

#endif /* _MATCHTYPE_H_ */
