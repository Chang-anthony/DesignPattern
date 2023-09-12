#include "../include/Journey.h"
#include "../include/Chapter.h"
#include "../include/Adventurer.h"
#include "../include/Student.h"
#include "../include/TourGroup.h"
#include "../include/Mission.h"


Journey::Journey(std::string name,std::string description,int price,
        const std::vector<Chapter*>& chapters,
        const std::vector<Adventurer*>& adventurers,
        const std::vector<TourGroup*>& tourgroups)
{
    this->SetName(name);
    this->SetDescription(description);
    this->SetPrice(price);
    this->SetChapters(chapters);
    this->SetAdventurers(adventurers);
}

Adventurer* Journey::Join(Student* student)
{
    utils::RequireNonNull(student);
    //學生加入旅程
    std::cout << "學員 " << student->GetAccount() << "加入旅程 " << this->GetName() << std::endl;
    int size = this->adventurers.size() + 1;
    Adventurer* adventurer = new Adventurer(size,student,this);
    
    //建立與學生的雙向關聯
    this->adventurers.push_back(adventurer);
    student->GetAdventurers().push_back(adventurer);

    //分配第一個任務給冒險者
    Mission* first = this->chapters[0]->GetFirstMission();
    adventurer->CarryOnMission(first);

    //匹配旅團
    TourGroup* group = this->MatchTourGroup(adventurer);
    //建立Adventurer 與 旅團的雙向關聯
    group->Add(adventurer);
    std::cout << "【旅程】冒險者 " << adventurer->GetStudent()->GetAccount() 
                << " 加入旅程" << this->GetName() << " 匹配至旅團 :" << group->GetID() << std::endl;

    return adventurer;
}

TourGroup* Journey::MatchTourGroup(Adventurer* adventurer)
{   
    utils::RequireNonNull(adventurer);
    if(!this->tourgroups.empty())
    {
        return this->tourgroups[(int)rand() % this->tourgroups.size()];
    }

    return new TourGroup(1,{adventurer});
}


std::string Journey::GetName()
{
    return this->name;
}

std::string Journey::GetDescription()
{
    return this->description;
}

int Journey::GetPrice()
{
    return this->price;
}

std::vector<Chapter*> Journey::GetChapters()
{
    return this->chapters;
}

std::vector<Adventurer*> Journey::GetAdventurers()
{
    return this->adventurers;
}

std::vector<TourGroup*> Journey::GetTourGroups()
{
    return this->tourgroups;
}

void Journey::SetName(std::string name)
{
    utils::LengthShouldBe(name,1,30);
    this->name = name;
}

void Journey::SetDescription(std::string description)
{
    utils::LengthShouldBe(description,0,300);
    this->description = description;
}

void Journey::SetPrice(int price)
{
    utils::ValShouldBigger(price,1);
    this->price = price;
}

void Journey::SetChapters(const std::vector<Chapter*>& chapter)
{
    utils::RequireNonNull(&chapter);
    this->chapters = chapter;
}

void Journey::SetAdventurers(const std::vector<Adventurer*>& adventurers)
{
    utils::RequireNonNull(&adventurers);
    this->adventurers = adventurers;
}

void Journey::SetTourGroups(const std::vector<TourGroup*>& tourgroup)
{
    utils::RequireNonNull(&tourgroups);
    this->tourgroups = tourgroup;
}

Journey::~Journey()
{
    
}