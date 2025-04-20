#ifndef _AI_H_
#define _AI_H_

#include "Role.hpp"
#include <string>

class AI : public Role {
private:
    int seed;

public:
    AI(int hp, int mp, int str, const std::string& name, int seed);
    AI(int hp, int mp, int str, const std::string& name, const std::vector<Skill*>& skills, int seed);

    int getSeed() const;
    void setSeed(int newSeed);
};

#endif /* _AI_H_ */
