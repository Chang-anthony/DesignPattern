#include "Skill.hpp"

// Constructor and Destructor
Skill::Skill() = default;
Skill::~Skill() = default;

// Getters
std::string Skill::getName() const { return name; }
int Skill::getMp() const { return mp; }
int Skill::getTargetEnemy() const { return targetEnemy; }
int Skill::getTargetFriend() const { return targetFriend; }

// Setters
void Skill::setName(const std::string& name) { this->name = name; }
void Skill::setMp(int mp) { this->mp = mp; }
void Skill::setTargetEnemy(int targetEnemy) { this->targetEnemy = targetEnemy; }
void Skill::setTargetFriend(int targetFriend) { this->targetFriend = targetFriend; }
