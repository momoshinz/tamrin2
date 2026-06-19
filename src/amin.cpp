// amin.cpp
#include "amin.h"
#include "team.h"
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

aminImeni::aminImeni() : hero("Amin Imeni", 500)
{
    ability1Cost = 3;
    ability2Cost = 3;
    specialCost = 4;
}

void aminImeni::ability1(hero *target, team *myTeam, team *enemyTeam)
{
    int damage = 55;

    if (target->getHp() <= damage)
    {
        damage = 110;
        cout << "\n-> " << target->getName() << " IS KILLED WITH DAMAGE DOUBLED TO 110!\n";
    }

    target->takeDamage(damage);
    cout << "\n-> " << target->getName() << " TAKES " << damage << " DAMAGE!\n   New HP : "
         << target->getHp() << '\n';
}

void aminImeni::ability2(hero *target, team *myTeam, team *enemyTeam)
{
    target->takeDamage(25);
    cout << "\n-> " << target->getName() << " LOSES 25 HP!\n   New HP : "
         << target->getHp() << '\n';

    this->heal(75);
    cout << "\n-> " << this->getName() << " HEALS HIMSELF 75 HP!\n   New HP : "
         << this->getHp() << '\n';
}

void aminImeni::specialAbility(team *myTeam, team *enemyTeam)
{
    vector<hero *> aliveTeammates;
    for (int i = 0; i < myTeam->getSize(); i++)
    {
        hero *member = myTeam->getHero(i);
        if (member != this && member->getHp() > 0)
        {
            aliveTeammates.push_back(member);
        }
    }

    int hitCount = 0;
    for (hero *teammate : aliveTeammates)
    {
        if (hitCount >= 2)
            break;
        teammate->takeDamage(30);
        cout << "\n-> " << teammate->getName() << " TAKES 30 DAMAGE!\n   New HP : "
             << teammate->getHp() << '\n';
        hitCount++;
    }

    if (hitCount == 0)
    {
        cout << "\nNO OTHER ALIVE TEAMMATE TO HIT!\n";
    }

    vector<hero *> aliveEnemies;
    for (int i = 0; i < enemyTeam->getSize(); i++)
    {
        hero *member = enemyTeam->getHero(i);
        if (member->getHp() > 0)
        {
            aliveEnemies.push_back(member);
        }
    }
    if (!aliveEnemies.empty())
    {
        int randomIndex = rand() % aliveEnemies.size();
        hero *randomEnemy = aliveEnemies[randomIndex];
        randomEnemy->takeDamage(250);
        cout << "\n-> " << randomEnemy->getName() << " TAKES 250 DAMAGE!\n   New HP : "
             << randomEnemy->getHp() << '\n';
    }
}

void aminImeni::abilityMessage(int abilityNum)
{
    if (abilityNum == 1)
    {
        cout << "\nLAST BULLET . . .\n";
        cout << "\nDeal 55 damage to an enemy.\n{DOUBLED TO 110 IF IT KILLS!}\n";
    }
    else if (abilityNum == 2)
    {
        cout << "\nSELF HIT . . .\n";
        cout << "\nTake 25 HP from a teammate, heal self by 75 HP!\n";
    }
    else if (abilityNum == 3)
    {
        cout << "\n-[PANIC SHOUT]- \"ONE ... TWO ... THREE ... BOOM!\"\n";
        cout << "\n250 damage to a random enemy and 30 damage to 2 teammates!\n";
    }
}

bool aminImeni::isTargetFromOwnTeam(int abilityNum)
{
    if (abilityNum == 2)
        return true;
    return false;
}

bool aminImeni::isAutoTarget(int abilityNum)
{
    if (abilityNum == 3)
        return true;
    return false;
}