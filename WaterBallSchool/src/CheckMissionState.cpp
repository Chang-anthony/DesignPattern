#include "../include/CheckMissionState.h"
#include "../include/Student.h"
#include "../include/Mission.h"


CheckMissionState::CheckMissionState(Student* studnet,Mission* mission)
{
    this->currentstate = state::inprogress;
    SetStudent(studnet);
    SetMission(mission);
}

void CheckMissionState::CompleteMission()
{
    this->currentstate = state::done;
    std::cout << "【任務】學員 " << this->student->GetAccount() << " 已成功完成任務" << this->mission->GetName() << std::endl;
    this->student->GainExp(this->mission->ExpAward());
}

Student* CheckMissionState::GetStuent()
{
    return this->student;
}

Mission* CheckMissionState::GetMission()
{
    return this->mission;
}

void CheckMissionState::SetStudent(Student* student)
{
    utils::RequireNonNull(student);
    this->student = student;
}

void CheckMissionState::SetMission(Mission *mission)
{
    utils::RequireNonNull(mission);
    this->mission = mission;
}

CheckMissionState::~CheckMissionState()
{

}