#include "../include/CheckMissionState.h"
#include "../include/Student.h"
#include "../include/Mission.h"


CheckMissionState::CheckMissionState(Student* studnet,Mission* mission)
{
    this->currentstate = state::inprogress;
    this->student = studnet;
    this->mission = mission;
}

void CheckMissionState::CompleteMission()
{
    this->currentstate = state::done;
    std::cout << "【任務】學員 " << this->student->GetAccount() << " 已成功完成任務" << this->mission->GetName() << std::endl;
    this->student->GainExp(this->mission->ExpAward());
}

CheckMissionState::~CheckMissionState()
{

}