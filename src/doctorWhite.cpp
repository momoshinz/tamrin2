#include "doctorWhite.h"
#include "hero.h"
#include "team.h"
#include <iostream>
#include <random>

using namespace std;

DoctorWhite::DoctorWhite()
    : hero("Doctor White", 550)
{
    dead = false;
    damagePercent = 0;
    damageDuration = 0;

    ability1Cost = 3;
    ability2Cost = 4;
    specialCost = 4;
    setRageRequired(4);
}

void DoctorWhite::ability1(hero *target, team *myTeam, team *enemyTeam)
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

    if (!aliveTeammates.empty())
    {
        int randomIndex = rand() % aliveTeammates.size();
        hero *randomTeammate = aliveTeammates[randomIndex];
        randomTeammate->heal(40);
        cout << "\n-> " << randomTeammate->getName() << " GOT HEALED!\n   New HP : "
             << randomTeammate->getHp() << endl;
    }
    else
    {
        cout << "NO OTHER ALIVE TEAMMATE TO HEAL!\n";
    }

    target->takeDamage(40);
    cout << "\n-> " << target->getName() << " GOT DAMAGED!\n   New HP : "
         << target->getHp() << endl;
}

void DoctorWhite::ability2(hero *target, team *myTeam, team *enemyTeam)
{
    target->addDamageBuff(20, 2);

    cout << "\n-> " << target->getName()
         << " GETS 20 PERCENT DAMAGE BUFF FOR 2 ROUNDS!\n";
}

void DoctorWhite::specialAbility(team *myTeam, team *enemyTeam)
{
    for (int i = 0; i < myTeam->getSize(); i++)
    {
        hero *member = myTeam->getHero(i);
        if (member != this && member->getHp() == 0)
        {
            member->revive(200);
            cout << "\n-> " << member->getName() << " IS REVIVED!\n   New HP : ";
            return;
        }
    }

    cout << "\nNO DEAD TEAMMATE TO REVIVE!\n";
}

string DoctorWhite::getAbilityName(int abilityNum)
{
    if (abilityNum == 1)
        return "Aspirin";
    if (abilityNum == 2)
        return "Doping";
    if (abilityNum == 3)
        return "Operation Room";
    return "";
}

void DoctorWhite::abilityMessage(int abilityNum)
{
    if (abilityNum == 1)
    {
        cout << "\n> ASPIRIN . . .\n";
        cout << "\nA random teammate will be healed by 40 HP!\nChosen enemy will take 40 damage!\n";
    }
    else if (abilityNum == 2)
    {
        cout << "\n> DOPING . . .\n";
        cout << "\nChosen teammate will be given 20 percent DAMAGE BUFF for 2 rounds!\n";
    }
    else if (abilityNum == 3)
    {
        cout << "\n-[OPERATION ROOM]- \"BRING HIM TO THE TABLE ... HE'LL SURVIVE IF HE'S LUCKY!\"\n";
        cout << "A dead teammate will be REVIVED with 200 HP!\n";
    }
}

bool DoctorWhite::isTargetFromOwnTeam(int abilityNum)
{
    if (abilityNum == 2)
        return true;
    if (abilityNum == 3)
        return true;
    return false;
}

bool DoctorWhite::isAutoTarget(int abilityNum)
{
    if (abilityNum == 3)
        return true;
    return false;
}