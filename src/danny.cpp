#include "danny.h"
#include <iostream>

using namespace std;

DannyGolang::DannyGolang()
    : hero("Danny Golang", 600)
{
    ability1Cost = 2;
    ability2Cost = 4;
    specialCost = 4;

    lastTarget = nullptr;
    consecutiveHits = 0;
}
void DannyGolang::ability1(hero *target, team *myTeam, team *enemyTeam)
{
    int damage = 20;

    if (lastTarget == target && consecutiveHits > 0)
    {
        damage = 20 * 1.6;
        cout << "\nSAME TARGET! DAMAGE MULTIPLIED BY 1.6!\n";
    }
    else
    {
        consecutiveHits = 0;
    }
    target->takeDamage(damage);
    cout << "\n-> " << target->getName() << " TAKES " << damage << " DAMAGE\n   New HP : "
         << target->getHp() << '\n';

    lastTarget = target; // to save for the next round
    consecutiveHits++;
}

void DannyGolang::ability2(hero *target, team *myTeam, team *enemyTeam)
{
    target->takeDamage(50);
    cout << "\n-> " << target->getName() << " TAKES 50 DAMAGE\n   New HP : "
         << target->getHp() << '\n';

    hero *highestHpEnemy = nullptr;
    int maxHp = -1;

    for (int i = 0; i < enemyTeam->getSize(); i++)
    {
        hero *member = enemyTeam->getHero(i);
        if (member->getHp() > 0 && member != target && member->getHp() > maxHp)
        {
            maxHp = member->getHp();
            highestHpEnemy = member;
        }
    }
    if (highestHpEnemy != nullptr)
    {
        highestHpEnemy->takeDamage(50);
        cout << "\n-> " << highestHpEnemy->getName() << " TAKES 50 DAMAGE\n   New HP : "
             << highestHpEnemy->getHp() << '\n';
    }
    else
    {
        cout << "NO OTHER ENEMY TO HIT ANYMORE!\n";
    }
}

void DannyGolang::specialAbility(team *myTeam, team *enemyTeam)
{
    hero *lowestHpTeammate = nullptr;
    int minHp = INT_MAX;

    for (int i = 0; i < myTeam->getSize(); i++)
    {
        hero *member = myTeam->getHero(i);
        if (member->getHp() > 0 && member->getHp() < minHp)
        {
            minHp = member->getHp();
            lowestHpTeammate = member;
        }
    }
    if (lowestHpTeammate != nullptr)
    {
        lowestHpTeammate->setShield(250, 2);
        cout << "\n-> " << lowestHpTeammate->getName()
             << " GETS 250 SHIELD FOR 2 ROUNDS!\n";
    }
    else
    {
        cout << "\nNO OTHER ALIVE TEAMMATE TO SHIELD!\n";
    }
}

void DannyGolang::abilityMessage(int abilityNum)
{
    if (abilityNum == 1)
    {
        cout << "\nLOCK . . .\n";
        cout << "\nA chosen enemy will take 20 damage.\n{1.6x IF REPEATED ON SAME TARGET!}\n";
    }
    else if (abilityNum == 2)
    {
        cout << "\nELEPHANT KILLER . . .\n";
        cout << "\nA chosen enemy and an enemy with highest HP will take 50 damage!\n";
    }
    else if (abilityNum == 3)
    {
        cout << "\n-[FAMILY STRONGHOLD]- \"NOBODY CROSSES THIS LINE!\"\n";
        cout << "\nA teammate with lowest HP will be given 250 shield for 2 rounds!\n";
    }
}

bool DannyGolang::isTargetFromOwnTeam(int abilityNum)
{
    if (abilityNum == 3)
        return true;
    return false;
}

bool DannyGolang::isAutoTarget(int abilityNum)
{
    if (abilityNum == 3)
        return true;
    return false;
}