#pragma once
#include "hero.h"

class tahaB : public hero
{
private:
    hero *markedEnemy;
    int markedRound;

public:
    tahaB();

    void ability1(hero *target, team *myTeam, team *enemyTeam) override;
    void ability2(hero *target, team *myTeam, team *enemyTeam) override;
    void specialAbility(team *myTeam, team *enemyTeam) override;
    string getAbilityName(int abilityNum) override;

    void abilityMessage(int abilityNum) override;
    bool isTargetFromOwnTeam(int abilityNum) override;
    bool isAutoTarget(int abilityNum) override;

    void applyMarkDamage(team *enemyTeam);
};