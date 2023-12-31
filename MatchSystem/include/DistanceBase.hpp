#ifndef _DISTANCEBASE_H_
#define _DISTANCEBASE_H_

#include "../include/MatchType.hpp"



class DistanceBase : public MatchType
{
private:
    /* data */
public:
    DistanceBase(/* args */);
    ~DistanceBase();

    std::vector<Individual*> Match(Individual* preson,std::set<Individual*> individuals) override;
    Individual* result(Individual* person,std::set<Individual*> individuals) override;
};


#endif /* _DISTANCEBASE_H_ */
