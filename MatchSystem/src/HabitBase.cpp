#include "../include/HabitBase.hpp"
#include "../include/Individual.hpp"
#include "../include/Habit.hpp"
#include <algorithm>

typedef std::pair<int,Individual*> P;

HabitBase::HabitBase(/* args */) : MatchType()
{
}

std::vector<Individual*> HabitBase::Match(Individual* preson,std::set<Individual*> individuals)
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


    int max_count = -1;
    std::set<std::string> presonhabit = std::set<std::string>();
    for (auto habit:preson->GetHabits())
    {
        presonhabit.insert(habit->GetHabit());
    }
    
    for(auto v : can_choose)
    {
        int count = 0;
        for(auto habit:v->GetHabits())
        {
            if(presonhabit.find(habit->GetHabit()) != presonhabit.end())
                count++;
        }
        helper.push_back({count,v});
    }

    std::sort(helper.begin(),helper.end(),[](const P& a,const P& b)
    {
        if(a.first == b.first)
            return a.second->GetID() < b.second->GetID();
        else
            return a.first > b.first;
    });

    for(auto p:helper)
        result.push_back(p.second);
    
    return result;
}

Individual* HabitBase::result(Individual* person,std::set<Individual*> individuals)
{
    std::vector<Individual*> result = this->Match(person,individuals);
    return result[0];
}

HabitBase::~HabitBase()
{
}