#include "tahaB.h"
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

tahaB::tahaB()
    : hero("Taha Bozorge", 500)
{
    ability1Cost = 3;
    ability2Cost = 4;
    specialCost = 3;
    setRageRequired(4);

    markedEnemy = nullptr;
    markedRound = 0;
}

void tahaB::ability1(hero *target, team *myTeam, team *enemyTeam)
{
    int damage = 30;
    int hitCount = 0;

    for (int i = 0; i < enemyTeam->getSize(); i++)
    {
        hero *enemy = enemyTeam->getHero(i);
        if (enemy->getHp() > 0)
        {
            enemy->takeAreaDamage(damage);
            cout << "\n-> " << enemy->getName()
                 << " TAKES " << damage << " DAMAGE\n"
                 << "   New HP : " << enemy->getHp() << '\n';
            hitCount++;
        }
    }

    if (hitCount == 0)
    {
        cout << "\nNO ALIVE ENEMIES TO HIT!\n";
    }
}

void tahaB::ability2(hero *target, team *myTeam, team *enemyTeam)
{
    if (target != nullptr && target->getHp() > 0)
    {
        target->takeDamage(90);
        cout << "\n-> " << target->getName()
             << " TAKES 90 DAMAGE!\n"
             << "   New HP : " << target->getHp() << '\n';

        this->setInvisible(1);
    }
    else
    {
        cout << "\nNO VALID ENEMY TARGET!\n";
    }
}

void tahaB::specialAbility(team *myTeam, team *enemyTeam)
{
    vector<hero *> aliveEnemies;
    for (int i = 0; i < enemyTeam->getSize(); i++)
    {
        hero *enemy = enemyTeam->getHero(i);
        if (enemy->getHp() > 0)
        {
            aliveEnemies.push_back(enemy);
        }
    }

    if (aliveEnemies.empty())
    {
        cout << "\nNO ALIVE ENEMIES TO MARK!\n";
        return;
    }

    int randomIndex = rand() % aliveEnemies.size();
    markedEnemy = aliveEnemies[randomIndex];
    markedRound = 1;

    cout << "\n-> " << markedEnemy->getName()
         << " IS MARKED FOR 360 DAMAGE NEXT ROUND!\n";

    if (markedEnemy->getHp() <= 360)
    {
        cout << "\n[!] WARNING : " << markedEnemy->getName()
             << " WILL DIE NEXT ROUND!\n";
    }
}

void tahaB::applyMarkDamage(team *enemyTeam)
{
    if (markedEnemy == nullptr || markedRound == 0)
        return;

    bool enemyStillAlive = false;
    for (int i = 0; i < enemyTeam->getSize(); i++)
    {
        if (enemyTeam->getHero(i) == markedEnemy && markedEnemy->getHp() > 0)
        {
            enemyStillAlive = true;
            break;
        }
    }

    if (!enemyStillAlive)
    {
        markedEnemy = nullptr;
        markedRound = 0;
        return;
    }

    if (markedEnemy->getHp() <= 360)
    {
        markedEnemy->setDead(true);
        cout << "\n-> " << markedEnemy->getName()
             << " TAKES 360 DAMAGE AND DIES!\n";
    }
    else
    {
        markedEnemy->takeDamage(200);
        cout << "\n-> " << markedEnemy->getName()
             << " TAKES 200 DAMAGE!\n"
             << "   New HP : " << markedEnemy->getHp() << '\n';
    }

    markedEnemy = nullptr; // to reset mark
    markedRound = 0;
}

string tahaB::getAbilityName(int abilityNum)
{
    if (abilityNum == 1)
        return "Volley";
    if (abilityNum == 2)
        return "X-Ray";
    if (abilityNum == 3)
        return "Brother's revenge";
    return "";
}

void tahaB::abilityMessage(int abilityNum)
{
    if (abilityNum == 1)
    {
        cout << "\n> VOLLEY . . .\n";
        cout << "\n30 damage to ALL enemies!\n";
    }
    else if (abilityNum == 2)
    {
        cout << "\n> X-RAY . . .\n";
        cout << "\nChosen enemy will take 90 damage!\n{ BECOME INVISIBLE FOR 1 ROUND! }\n";
    }
    else if (abilityNum == 3)
    {
        cout << "\n-[BROTHER'S REVENGE]- \"THIS ONE WAS FOR MY LITTLE BROTHER ... NOW ITS YOUR TURN!!\"\n";
        cout << "\nA random enemy will be MARKED for 360 damage next round!\n";
        cout << "* If HP LESS than 360 --> INSTANT KILL!\n";
        cout << "* If HP MORE than 360 --> takes 200 damage instead!\n";
    }
}

bool tahaB::isTargetFromOwnTeam(int abilityNum)
{
    return false;
}

bool tahaB::isAutoTarget(int abilityNum)
{
    if (abilityNum == 1)
        return true;
    if (abilityNum == 3)
        return true;
    return false;
}