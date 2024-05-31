#include <Patient.hpp>
#include <Case.hpp>


Patient::Patient(std::string id, std::string name, std::string gender, int age, float height, float weight)
{
    SetId(id);
    SetName(name);
    SetGender(gender);
    SetAge(age);
    SetHeight(height);
    SetWeight(weight);
    cases = std::vector<Case*>();
}

void Patient::AddCase(Case* newCase)
{
    utils::RequireNonNull(newCase);
    cases.push_back(newCase);
}

std::vector<Case*> Patient::GetCases()
{
    return cases;
}

std::string Patient::GetId()
{
    return id;
}

std::string Patient::GetName()
{
    return name;
}

std::string Patient::GetGender()
{
    return gender;
}

int Patient::GetAge()
{
    return age;
}

float Patient::GetHeight()
{
    return height;
}

float Patient::GetWeight()
{
    return weight;
}

void Patient::SetId(std::string id)
{
    std::string regex = "^[A-Z]\\d{9}$";
    this->id = utils::StrMustMatchRegex(id, regex);
}

void Patient::SetName(std::string name)
{
    utils::LengthShouldBe(name, 1, 30);
    this->name = name;
}

void Patient::SetGender(std::string gender)
{
    if (gender != "male" || gender != "female")
        throw std::invalid_argument("input gender not vaild");
    this->gender = gender;
}

void Patient::SetAge(int age)
{
    utils::ValShouldBe(age, 1, 180);
    this->age = age;
}

void Patient::SetHeight(float height)
{
    utils::ValShouldBe(height, (float)1.0, (float)500.0);
    this->height = height;
}

void Patient::SetWeight(float weight)
{
    utils::ValShouldBe(weight, (float)1.0, (float)500.0);
    this->weight = weight;
}

void Patient::SetCases(std::vector<Case*> cases)
{
    this->cases = cases;
}

Patient::~Patient()
{
}