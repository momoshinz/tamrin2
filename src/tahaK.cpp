#include "tahaK.h"
#include <iostream>
#include <climits>

using namespace std;

tahaK::tahaK()
    : hero("Taha Koochike", 500)
{
    ability1Cost = 2;
    ability2Cost = 4;
    specialCost = 4;
}

void tahaK::ability1(hero *target, team *myTeam, team *enemyTeam)
{
    hero *lowestHpTeammate = nullptr;
    int minHp = INT_MAX;

    for (int i = 0; i < myTeam->getSize(); i++)
    {
        hero *member = myTeam->getHero(i);
        if (member->getHp() > 0 && member != this && member->getHp() < minHp)
        {
            minHp = member->getHp();
            lowestHpTeammate = member;
        }
    }
    if (lowestHpTeammate != nullptr)
    {
        lowestHpTeammate->heal(20);
        cout << "\n-> "
             << lowestHpTeammate->getName()
             << " IS HEALED BY 20 HP\n   New HP : "
             << lowestHpTeammate->getHp() << '\n';
    }
    else
    {
        cout << "NO ALIVE TEAMMATE TO HEAL!\n";
    }

    target->takeDamage(30);
    cout << "\n-> " << target->getName()
         << " TAKES 30 HP DAMAGE\n"
         << "   New HP : " << target->getHp() << '\n';
}

void tahaK::ability2(hero* target, team* myTeam, team* enemyTeam)
{
    target->addHealOverTime(40, 2);
    cout << "\n-> " << target->getName()
         << " WILL HEAL 40 HP AT THE START OF EACH ROUND FOR 2 ROUNDS!\n";
}

void tahaK::specialAbility(team *myTeam, team *enemyTeam)
{
    hero *lowestHpTeammate = nullptr;
    int minHp = INT_MAX;

    for (int i = 0; i < myTeam->getSize(); i++)
    {
        hero *member = myTeam->getHero(i);
        if (member->getHp() > 0 && member !=this && member->getHp() < minHp)
        {
            minHp = member->getHp();
            lowestHpTeammate = member;
        }
    }

    if (lowestHpTeammate != nullptr)
    {
        lowestHpTeammate->heal(200);
        cout << "\n-> "
             << lowestHpTeammate->getName()
             << " IS HEALED BY 200 HP\n   New HP : "
             << lowestHpTeammate->getHp() << '\n';
    }
    else
    {
        cout << "NO ALIVE TEAMMATE TO HEAL!\n";
    }
}

void tahaK::abilityMessage(int abilityNum)
{
    if (abilityNum == 1)
    {
        cout << "\n> SHARP BLADE . . .\n";
        cout << "\nLowest HP teammate will be healed by 20 HP!\nAn enemy should be damaged 30 HP!\n";
    }
    else if (abilityNum == 2)
    {
        cout << "\n> BLOOD SERUM . . .\n";
        cout << "\nA teammate will be healed 40 HP for 2 rounds.\n";
    }
    else if (abilityNum == 3)
    {
        cout << "\n-[FULL QUARANTINE]- \"EVERYONE, STAY WHERE YOU ARE ... THIS AREA IS CONTAMINATED!\"\n";
        cout << "\nLowest HP teammate will be healed by 200 HP!\n";
    }
}

bool tahaK::isTargetFromOwnTeam(int abilityNum)
{
    if (abilityNum == 2)
        return true;
    if (abilityNum == 3)
        return true;
    return false;
}

bool tahaK::isAutoTarget(int abilityNum)
{
    if (abilityNum == 1)
        return false;
    if (abilityNum == 3)
        return true;
    return false;
}
