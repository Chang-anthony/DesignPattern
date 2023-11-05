#include "../include/Reverse.hpp"
#include "../include/Individual.hpp"

Reverse::Reverse(MatchType* reverse):MatchType(),reverse(reverse)
{
}

std::vector<Individual*> Reverse::Match(Individual* preson,std::set<Individual*> individuals)
{
    std::vector<Individual*> result = this->reverse->Match(preson,individuals);
    std::vector<Individual*> rev = std::vector<Individual*>(result.rbegin(),result.rend());
    return rev;
}

Individual* Reverse::result(Individual* preson,std::set<Individual*> individuals)
{
    std::vector<Individual*> result = this->Match(preson,individuals);
    return result[0];
}

Reverse::~Reverse()
{
}