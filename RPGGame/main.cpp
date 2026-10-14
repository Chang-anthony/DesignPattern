/*
* @author - (Anthony)
*/
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <fstream>
#include <Skill.hpp>
#include <BasicAttack.hpp>
#include <Poison.hpp>
#include <Waterball.hpp>
#include <Fireball.hpp>
#include <SelfHealing.hpp>
#include <Role.hpp>

#include <Role.hpp>
#include "SkillObserver.hpp"
#include "CurserObserver.hpp"
#include "Curse.hpp"
#include <vector>
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif



int main()
{
#ifdef _WIN32
    // 原始碼是 UTF-8，將 console 輸出改為 UTF-8 才能正確顯示中文
    SetConsoleOutputCP(CP_UTF8);
#endif

    Skill* skill = new Curse();

    Role* actor = new Role(500, 500, 50, "h");
    Role* actor2 = new Role(500, 500, 50, "h");
    Role* target = new Role(500, 500, 50, "h");
    
    skill->attack(actor, {target});
    std::vector<SkillObserver*> observser = target->getObservers();
    Role* test5 = observser[0]->getRole(); // Assuming Curse adds one observer

    skill->attack(actor2, {target});
    std::vector<SkillObserver*> observser2 = target->getObservers();
    Role* test3 = observser2[0]->getRole(); // Assuming Curse adds one observer
    Role* test4 = observser2[1]->getRole(); // Assuming Curse adds one observer

    skill->attack(actor, {target});
    std::vector<SkillObserver*> observser3 = target->getObservers();
    Role* test = observser3[0]->getRole(); // Assuming Curse adds one observer
    Role* test2 = observser3[1]->getRole(); // Assuming Curse adds one observer

    std::cout << "按下 Enter鍵 已結束遊戲" << std::endl;
    std::system("pause");
    return 0;
}