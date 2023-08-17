#include "CheckMissionState.h"
#include "Student.h"
#include "Mission.h"
#include <iostream>

// CheckMissionState::CheckMissionState(Student* studnet,Mission* mission)
// {
//     this->studnet = studnet;
//     this->mission = mission;
// }

void CheckMissionState::CompleteMission()
{
    this->currentstate = state::done;
    std::cout << "任務】學員 " << studnet->GetAccount() << " 已成功完成任務" << mission->GetName() << std::endl;
    studnet->GainExp(CheckMissionState::mission->ExpAward());
}
