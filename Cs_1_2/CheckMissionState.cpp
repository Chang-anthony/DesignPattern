#include "CheckMissionState.h"
#include "Student.h"
#include "Mission.h"



void CheckMissionState::CompleteMission()
{
    this->currentstate = state::done;
    std::cout << "任務】學員 " << studnet->GetAccount() << " 已成功完成任務" << mission->GetName() << std::endl;
    studnet->GainExp(mission->ExpAward());
}




