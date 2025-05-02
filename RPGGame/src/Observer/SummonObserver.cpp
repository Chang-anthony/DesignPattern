#include "SummonObserver.hpp"
#include <iostream>

SummonObserver::SummonObserver(Role* actor) : SkillObserver(actor) {

}


void SummonObserver::UntilDie() {
    std::cout << "SummonObserver: Observing until the summon dies." << std::endl;
}
