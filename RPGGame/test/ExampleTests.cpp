#include <iostream>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <vector>
#include <fstream>

#include "BasicAttack.hpp"
#include "Fireball.hpp"
#include "Waterball.hpp"
#include "OnePunch.hpp"
#include "SelfExplosion.hpp"
#include "SelfHealing.hpp"
#include "Poison.hpp"
#include "Cheerup.hpp"
#include "Petrochemical.hpp"
#include "Curse.hpp"
#include "Summon.hpp"
#include "Skill.hpp"

#include "Role.hpp"
#include "Hero.hpp"
#include "AI.hpp"

#include "PetrochemicaledState.hpp"
#include "PoisonedState.hpp"
#include "NormalState.hpp"
#include "CheerupedState.hpp"


#include "SkillObserver.hpp"
#include "Troop.hpp"
#include "Slime.hpp"
#include "SummonObserver.hpp"
#include "CurserObserver.hpp"


TEST(SkillTest, BasicAttackTest) {
    Skill* skill = new BasicAttack();
    EXPECT_EQ(skill->getMp(), 0); // Assuming BasicAttack requires 0 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 450); // Assuming BasicAttack deals 50 damage

}
TEST(SkillTest, FireballTest) {
    Skill* skill = new Fireball();
    EXPECT_EQ(skill->getMp(), 50); // Assuming Fireball requires 10 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");
    Role* target2 = new Hero(300, 500, 50, "h");

    skill->attack(actor, {target, target2});
    EXPECT_EQ(target->getHp(), 450); // Assuming Fireball deals 50 damage
    EXPECT_EQ(target2->getHp(), 250); // Assuming Fireball deals 50 damage
}
TEST(SkillTest, WaterballTest) {
    Skill* skill = new Waterball();
    EXPECT_EQ(skill->getMp(), 50); // Assuming Waterball requires 8 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 380); // Assuming Waterball deals 120 damage

}
TEST(SkillTest, OnePunchTest) {
    Skill* skill = new OnePunch();
    EXPECT_EQ(skill->getMp(), 180); // Assuming OnePunch requires 15 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 200); // Assuming OnePunch deals 300 damage

    Role* target2 = new Hero(400, 500, 50, "h");
    target2->setState(new CheerupedState());
    EXPECT_EQ(target2->getState()->getName(), "CheerupedState"); // Assuming CheerupedState is the initial state
    skill->attack(actor, {target2});
    EXPECT_EQ(target2->getHp(), 300); // Assuming OnePunch deals 300 damage
    EXPECT_EQ(target2->getState()->getName(), "NormalState"); // Assuming CheerupedState changes to NormalState after attack

    Role* target3 = new Hero(400, 500, 50, "h");
    target3->setState(new PetrochemicaledState());
    skill->attack(actor, {target3});
    EXPECT_EQ(target3->getHp(), 160); // Assuming OnePunch deals 300 damage
    EXPECT_EQ(target3->getState()->getName(), "PetrochemicaledState"); // Assuming PetrochemicaledState changes to NormalState after attack


    Role* target4 = new Hero(400, 500, 50, "h");
    target4->setState(new PoisonedState());
    skill->attack(actor, {target4});
    EXPECT_EQ(target4->getHp(), 160); // Assuming OnePunch deals 300 damage
    EXPECT_EQ(target4->getState()->getName(), "PoisonedState"); // Assuming PoisonedState changes to NormalState after attack


    Role* target5 = new Hero(200, 500, 50, "h");
    target5->setState(new NormalState());
    skill->attack(actor, {target5});
    EXPECT_EQ(target5->getHp(), 100); // Assuming OnePunch deals 300 damage

}


TEST(SkillTest, SelfExplosionTest) {
    Skill* skill = new SelfExplosion();
    EXPECT_EQ(skill->getMp(), 200); // Assuming SelfExplosion requires 20 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 350); // Assuming SelfExplosion deals 150 damage
    EXPECT_EQ(actor->getHp(), 0); // Actor self-damage

}
TEST(SkillTest, SelfHealingTest) {
    Skill* skill = new SelfHealing();
    EXPECT_EQ(skill->getMp(), 50); // Assuming SelfHealing requires 5 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");

    skill->attack(actor, {target});
    EXPECT_EQ(actor->getHp(), 650); // Assuming SelfHealing heals 150 HP
    EXPECT_EQ(target->getHp(), 500); // Target's HP should remain unchanged

}
TEST(SkillTest, PoisonTest) {
    Skill* skill = new Poison();
    EXPECT_EQ(skill->getMp(), 80); // Assuming Poison requires 7 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 500); // Assuming Poison deals 50 damage
    EXPECT_EQ(target->getState()->getName(), "PoisonedState"); // Assuming Poison changes target's state to PoisonedState

}
TEST(SkillTest, CheerupTest) {
    Skill* skill = new Cheerup();
    EXPECT_EQ(skill->getMp(), 100); // Assuming Cheerup requires 3 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 500); // Target's HP should remain unchanged
    EXPECT_EQ(target->getState()->getName(), "CheerupedState"); // Assuming Cheerup changes target's state to CheerupedState
}
TEST(SkillTest, PetrochemicalTest) {
    Skill* skill = new Petrochemical();
    EXPECT_EQ(skill->getMp(), 100); // Assuming Petrochemical requires 12 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");
    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 500); // Target's HP should remain unchanged
    EXPECT_EQ(target->getState()->getName(), "PetrochemicaledState"); // Assuming Petrochemical changes target's state to PetrochemicaledState

}
TEST(SkillTest, CurseTest) {
    Skill* skill = new Curse();
    EXPECT_EQ(skill->getMp(), 100); // Assuming Curse requires 9 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* actor2 = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");
    
    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 500); // Target's HP should remain unchanged
    std::vector<SkillObserver*> observser = target->getObservers();
    EXPECT_EQ(observser[0]->getRole(), actor); // Assuming Curse adds one observer

    skill->attack(actor2, {target});
    EXPECT_EQ(target->getHp(), 500); // Target's HP should remain unchanged
    std::vector<SkillObserver*> observser2 = target->getObservers();
    EXPECT_EQ(observser2[0]->getRole(), actor); // Assuming Curse adds one observer
    EXPECT_EQ(observser2[1]->getRole(), actor2); // Assuming Curse adds one observer

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 500); // Target's HP should remain unchanged
    std::vector<SkillObserver*> observser3 = target->getObservers();
    EXPECT_EQ(observser3.size(), 2); // Assuming Curse adds one observer
    EXPECT_EQ(observser3[0]->getRole(), actor); // Assuming Curse adds one observer
    EXPECT_EQ(observser3[1]->getRole(), actor2); // Assuming Curse adds one observer
    
}

TEST(SkillTest, SummonTest) {
    Skill* skill = new Summon();
    EXPECT_EQ(skill->getMp(), 150); // Assuming Summon requires 25 MP

    Role* actor = new Hero(500, 500, 50, "h");
    Role* target = new Hero(500, 500, 50, "h");
    Troop* troop = new Troop();
    Troop* troop2 = new Troop();

    troop->addRole(actor);
    troop2->addRole(target);

    skill->attack(actor, {target});
    EXPECT_EQ(target->getHp(), 500); // Target's HP should remain unchanged

    std::vector<Role*> roles = troop->getRoles();
    EXPECT_EQ(roles.size(), 2); // Assuming Summon adds one observer
    EXPECT_EQ(roles[1]->getName(), "Slime"); // Assuming Summon adds one observer

    std::vector<SkillObserver*> observser3 = target->getObservers();
    EXPECT_EQ(observser3.size(), 0); // Assuming Summon adds one observer
    EXPECT_EQ(roles[1]->getObservers().size(), 1); // Assuming Summon adds one observer
    EXPECT_EQ(roles[1]->getObservers()[0]->getRole(), actor); // Assuming Summon adds one observer

}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}

