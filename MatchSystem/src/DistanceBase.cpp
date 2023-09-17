#include "../include/DistanceBase.hpp"
#include "../include/Individual.hpp"
#include "../include/Coord.hpp"
#include <cmath>

DistanceBase::DistanceBase(/* args */) : MatchType()
{
}

Individual* DistanceBase::Match(Individual* preson,std::set<Individual*> individuals)
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

    Individual* matched = nullptr;

    if(!preson->GetReverse())
    {
        double distance = INT_MAX - 1 ;
        for(auto v:can_choose)
        {
            double disx = preson->GetCoord()->GetX() - v->GetCoord()->GetX();
            double disy = preson->GetCoord()->GetY() - v->GetCoord()->GetY();
            double dis = std::sqrt((disx*disx + disy*disy));
            if(dis <= distance)
            {
                matched = !matched ? v : dis < distance ? v : matched->GetID() < v->GetID() ? matched : v;
                distance = std::min(distance,dis);
            }
        }
    }
    else
    {
        double distance = INT_MAX - 1 ;
        for(auto v:can_choose)
        {
            double disx = preson->GetCoord()->GetX() - v->GetCoord()->GetX();
            double disy = preson->GetCoord()->GetY() - v->GetCoord()->GetY();
            double dis = std::sqrt((disx*disx + disy*disy));
            if(dis >= distance)
            {
                matched = !matched ? v : dis > distance ? v : matched->GetID() > v->GetID() ? matched : v;
            }
        }

    }

    return matched;
}

DistanceBase::~DistanceBase()
{
}
