#ifndef _MATCHSYSTEM_H_
#define _MATCHSYSTEM_H_

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <cmath>
#include <algorithm>

class Individual;

class MatchSystem
{
private:
    /* data */
    std::set<Individual*> individuals;
public:
    MatchSystem(/* args */);
    ~MatchSystem();

    void AddIndividuals(Individual* individual);
    Individual* Match(Individual* person);

    //get
    std::set<Individual*> GetIndividuals();

    //set
    void SetIndividuals(std::set<Individual*> individuals);
};

#endif /* _MATCHSYSTEM_H_ */
