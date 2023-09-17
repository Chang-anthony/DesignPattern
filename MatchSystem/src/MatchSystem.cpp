#include "../include/MatchSystem.hpp"
#include "../include/Individual.hpp"
#include "../include/utils/utils.h"
#include "../include/Coord.hpp"
#include "../include/Habit.hpp"

MatchSystem::MatchSystem(/* args */)
{
    this->individuals = std::set<Individual*>();
}

Individual* MatchSystem::Match(Individual* person)
{
    std::string match = person->GetPreferMatch();

    auto tovector = [](std::set<Individual*> individuals)
    {
        std::vector<Individual*> v = std::vector<Individual*>();
        for(auto p:individuals)
            v.push_back(p);
        return v;
    }; 

    std::vector<Individual*> can_choose = tovector(this->GetIndividuals());
    can_choose.erase(std::remove_if(can_choose.begin(),can_choose.end(),[person](Individual* remove)
    {
        return remove == person;
    }),can_choose.end());

    Individual* matched = nullptr;


    //TODO: match method v1 need to done
    if(!person->GetReverse())
    {
        if(match == "distance")
        {
            double distance = INT_MAX - 1 ;
            for(auto v:can_choose)
            {
                double disx = person->GetCoord()->GetX() - v->GetCoord()->GetX();
                double disy = person->GetCoord()->GetY() - v->GetCoord()->GetY();
                double dis = std::sqrt((disx*disx + disy*disy));
                if(dis <= distance)
                {
                    matched = !matched ? v : dis < distance ? v : matched->GetID() < v->GetID() ? matched : v;
                    distance = std::min(distance,dis);
                }
            }
        }
        else if(match == "habit")
        {
            int max_count = -1;
            std::set<std::string> presonhabit = std::set<std::string>();
            for (auto habit:person->GetHabits())
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
    }
    else
    {
        if(match == "distance")
        {
            double distance = INT_MAX - 1 ;
            for(auto v:can_choose)
            {
                double disx = person->GetCoord()->GetX() - v->GetCoord()->GetX();
                double disy = person->GetCoord()->GetY() - v->GetCoord()->GetY();
                double dis = std::sqrt((disx*disx + disy*disy));
                if(dis >= distance)
                {
                    matched = !matched ? v : dis > distance ? v : matched->GetID() > v->GetID() ? matched : v;
                }
            }
        }
        else if(match == "habit")
        {
            int max_count = INT_MAX - 1;
            std::set<std::string> presonhabit = std::set<std::string>();
            for (auto habit:person->GetHabits())
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
    }

    return matched;
}

void MatchSystem::AddIndividuals(Individual* individual)
{
    utils::RequireNonNull(individual);
    this->individuals.insert(individual);
}

std::set<Individual*> MatchSystem::GetIndividuals()
{
    return individuals;
}

void MatchSystem::SetIndividuals(std::set<Individual*> individuals)
{
    utils::RequireNonNull(&individuals);
    this->individuals = individuals;
}

MatchSystem::~MatchSystem()
{
}