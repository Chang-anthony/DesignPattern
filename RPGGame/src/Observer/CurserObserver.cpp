#include "CurserObserver.hpp"
#include <iostream>

CurserObserver::CurserObserver(Role* actor) : SkillObserver(actor) {

}


void CurserObserver::UntilDie() {
    std::cout << "CurserObserver: Observing until the curse effect ends." << std::endl;
}
