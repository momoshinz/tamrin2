#pragma once
#include "hero.h"

class tahaK : public hero
{
public:
    tahaK();

    void ability1(hero *target, team *myTeam, team *enemyTeam) override;
    void ability2(hero* target, team* myTeam, team* enemyTeam) override;
    void specialAbility(team *myTeam, team *enemyTeam) override;

    void abilityMessage(int abilityNum) override;
    bool isTargetFromOwnTeam(int abilityNum) override;
    bool isAutoTarget(int abilityNum) override;
};