#include "../include/DistanceBase.hpp"
#include "../include/Individual.hpp"
#include "../include/Coord.hpp"
#include <cmath>
#include <algorithm>

typedef std::pair<double,Individual*> P;

DistanceBase::DistanceBase(/* args */) : MatchType()
{
}

std::vector<Individual*> DistanceBase::Match(Individual* preson,std::set<Individual*> individuals)
{
    auto tovector = [](std::set<Individual*> individuals)
    {
        std::vector<Individual*> v = std::vector<Individual*>();
        for(auto p:individuals)
            v.push_back(p);
        return v;
    }; 

    std::vector<Individual*> can_choose = tovector(individuals);
    can_choose.erase(std::remove_if(can_choose.begin(),can_choose.end(),[preson](Individual* remove)
    {
        return remove == preson;
    }),can_choose.end());

    std::vector<P> helper = std::vector<P>();
    std::vector<Individual*> result = std::vector<Individual*>();

    double distance = INT_MAX - 1;
    for(auto v:can_choose)
    {
        double disx = preson->GetCoord()->GetX() - v->GetCoord()->GetX();
        double disy = preson->GetCoord()->GetY() - v->GetCoord()->GetY();
        double dis = std::sqrt((disx*disx + disy*disy));
        helper.push_back({dis,v});
    }

    //sort use first val
    std::sort(helper.begin(),helper.end(),[](const P& a,const P& b){
            if(a.first == b.first)
                return a.second->GetID() < b.second->GetID(); 
            //小排到大
            else
                return a.first < b.first;
    });

    for(auto r:helper)
        result.push_back(r.second);

    return result;
}

Individual* DistanceBase::result(Individual* person,std::set<Individual*> individuals)
{
    std::vector<Individual*> result = this->Match(person,individuals);
    return result[0];
}

DistanceBase::~DistanceBase()
{
}
