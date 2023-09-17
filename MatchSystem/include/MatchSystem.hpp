#ifndef _MATCHSYSTEM_H_
#define _MATCHSYSTEM_H_

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>

class Individual;
class MatchType;

class MatchSystem
{
private:
    /* data */
    std::set<Individual*> individuals;
    MatchType* matchtype;
public:
    MatchSystem(MatchType* matchtype);
    ~MatchSystem();

    void AddIndividuals(Individual* individual);
    Individual* Match(Individual* person);

    //get
    std::set<Individual*> GetIndividuals();
    MatchType* GetMatchType();

    //set
    void SetIndividuals(std::set<Individual*> individuals);
    void SetMatchType(MatchType* matchtype);
};

#endif /* _MATCHSYSTEM_H_ */
