#include "../include/MatchSystem.hpp"
#include "../include/Individual.hpp"
#include "../include/utils/utils.h"
#include "../include/MatchType.hpp"

MatchSystem::MatchSystem(MatchType* matchtype)
{
    this->individuals = std::set<Individual*>();
    SetMatchType(matchtype);
}

Individual* MatchSystem::Match(Individual* person)
{
    return this->matchtype->Match(person,this->individuals);
}

void MatchSystem::AddIndividuals(Individual* individual)
{
    utils::RequireNonNull(individual);
    this->individuals.insert(individual);
    individual->SetID(this->individuals.size());
}

std::set<Individual*> MatchSystem::GetIndividuals()
{
    return individuals;
}

MatchType* MatchSystem::GetMatchType()
{
    return matchtype;
}

void MatchSystem::SetIndividuals(std::set<Individual*> individuals)
{
    utils::RequireNonNull(&individuals);
    this->individuals = individuals;
}

void MatchSystem::SetMatchType(MatchType* matchtype)
{
    utils::RequireNonNull(matchtype);
    this->matchtype = matchtype;
}

MatchSystem::~MatchSystem()
{
}