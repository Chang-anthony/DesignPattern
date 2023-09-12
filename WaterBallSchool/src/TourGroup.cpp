#include "../include/TourGroup.h"
#include "../include/Adventurer.h"


TourGroup::TourGroup()
{

}

TourGroup::TourGroup(int id,const std::vector<Adventurer*>& adventurer)
{
    SetID(id);
    SetAdventurers(adventurer);
}

void TourGroup::Add(Adventurer* adventurer)
{
    utils::RequireNonNull(adventurer);
    adventurer->SetTourGroup(this);
}

int TourGroup::GetID()
{
    return this->id;
}

std::vector<Adventurer*> TourGroup::GetAdventurers()
{
    return this->adventurers;
}

void TourGroup::SetID(int id)
{
    utils::ValShouldBigger(id,0);
    this->id = id;
}

void TourGroup::SetAdventurers(const std::vector<Adventurer*> &adventurers)
{
    utils::RequireNonNull(&adventurers);
    this->adventurers = adventurers;

}

TourGroup::~TourGroup()
{

}

