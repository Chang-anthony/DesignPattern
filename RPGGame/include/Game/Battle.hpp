#ifndef BATTLE_HPP
#define BATTLE_HPP

class Troop;

class Battle {
private:
    Troop* ally;  // Ally troop
    Troop* enemy; // Enemy troop

public:
    Battle(Troop* ally, Troop* enemy);
    ~Battle();

    void startBattle();
};

#endif // BATTLE_HPP
