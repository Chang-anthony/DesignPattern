#include "../include/HabitBase.hpp"
#include "../include/Individual.hpp"
#include "../include/Habit.hpp"

HabitBase::HabitBase(/* args */) : MatchType()
{
}

Individual* HabitBase::Match(Individual* preson,std::set<Individual*> individuals)
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
            if(count >= max_count)
            {
                matched = !matched ? v : count > max_count ? v : matched->GetID() < v->GetID() ? matched : v;
                max_count = std::max(count,max_count);
            }
        }
    }
    else
    {
        int max_count = INT_MAX - 1;
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
            if(count <= max_count)
            {
                matched = !matched ? v : count < max_count ? v : matched->GetID() > v->GetID() ? matched : v;
                max_count = std::max(count,max_count);
            }
        }
    }

    return matched;
}

HabitBase::~HabitBase()
{
}