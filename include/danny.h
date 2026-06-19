// danny.h
#pragma once
#include "hero.h"

class DannyGolang : public hero
{
private:
    hero *lastTarget;
    int consecutiveHits; // shows how many times in a row the same target is damaged

public:
    DannyGolang();

    void ability1(hero *target, team *myTeam, team *enemyTeam) override;
    void ability2(hero *target, team *myTeam, team *enemyTeam) override;
    void specialAbility(team *myTeam, team *enemyTeam) override;
    string getAbilityName(int abilityNum) override;

    void abilityMessage(int abilityNum) override;
    bool isTargetFromOwnTeam(int abilityNum) override;
    bool isAutoTarget(int abilityNum) override;
};