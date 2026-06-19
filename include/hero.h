#pragma once
#include "team.h"
#include <string>

using namespace std;

class team;
class hero
{
protected:
    string name;
    int hp;
    int ability1Cost = 0;
    int ability2Cost = 0;
    int specialCost = 0;
    int damagePercent = 0;
    int damageDuration = 0;
    bool dead = false;
    int healAmount = 0;
    int healDuration = 0;
    int shieldAmount = 0;
    int shieldDuration = 0;
    bool isInvisible = false;
    int invisibleDuration = 0;

public:
    hero(string n, int h)
        : name(n), hp(h) {}

    string getName();
    int getHp();

    void setHp(int hp);

    virtual void ability1(hero *target, team *myTeam, team *enemyTeam) = 0;
    virtual void ability2(hero *target, team *myTeam, team *enemyTeam) = 0;
    virtual void specialAbility(team *myTeam, team *enemyTeam) = 0;
    virtual void abilityMessage(int abilityNum) {}
    virtual bool isTargetFromOwnTeam(int abilityNum) { return false; }
    virtual bool isAutoTarget(int abilityNum) { return false; }
    void takeDamage(int damage);
    void takeAreaDamage(int damage);  
    int getAbility1Cost();
    int getAbility2Cost();
    int getSpecialCost();
    void heal(int amount);
    void addDamageBuff(int percent, int duration);
    void revive(int hp);
    bool isDead();
    void clearNegativeEffects();
    int getDamagePercent();
    void decreaseDuration();
    bool hasDamageBuff();
    void setDead(bool dead);
    bool isAlive();
    void addHealOverTime(int amount, int duration);
    void applyHealOverTime();
    int getHealAmount() { return healAmount; }
    int getHealDuration() { return healDuration; }
    void setShield(int amount, int duration);
    int getShield() { return shieldAmount; }
    void reduceShield(int damage);
    void reduceShieldDuration();
    void setInvisible(int duration);
    bool getInvisible();
    void reduceInvisibleDuration();
    void applyInvisibility();

    virtual ~hero() {}
};
