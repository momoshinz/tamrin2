#include "game.h"
#include "hero.h"
#include "doctorWhite.h"
#include "tahaK.h"
#include "tahaB.h"
#include "danny.h"
#include "amin.h"
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

void Game::selectHeroes(int teamNum)
{
    vector<int> selectedHeroes;

    team *currentTeam = (teamNum == 1) ? &team1 : &team2;

    for (int i = 0; i < 3; i++)
    {
        int choice;

        cout << "\nTeam " << teamNum << " *** Choose Hero " << i + 1 << " : " << endl;
        cout << "1. Doctor White" << endl;
        cout << "2. Taha Koochike" << endl;
        cout << "3. Danny Golang" << endl;
        cout << "4. Amin Imeni" << endl;
        cout << "5. Taha Bozorge" << endl;

        cin >> choice;

        while (choice < 1 || choice > 5)
        {
            cout << "\nINVALID NUMBER!\nTry again : ";
            cin >> choice;
            cout << '\n';
        }

        bool exists = false;

        for (int hero : selectedHeroes)
        {
            if (hero == choice)
            {
                exists = true;
                break;
            }
        }

        if (exists)
        {
            cout << "\nHERO ALREADY SELECTED!\nTry again\n";
            i--;
            continue;
        }

        selectedHeroes.push_back(choice);

        hero *Hero = nullptr;

        switch (choice)
        {
        case 1:
            Hero = new DoctorWhite();
            break;
        case 2:
            Hero = new tahaK();
            break;
        case 3:
            Hero = new DannyGolang();
            break;
        case 4:
            Hero = new aminImeni();
            break;
        case 5:
            Hero = new tahaB();
            break;
        }

        currentTeam->addHero(Hero);
    }
}

int Game::checkWinner()
{
    int alive1 = team1.getAliveCount();
    int alive2 = team2.getAliveCount();

    if (alive1 > 0 && alive2 == 0)
        return 1;
    if (alive2 > 0 && alive1 == 0)
        return 2;
    if (alive1 == 0 && alive2 == 0)
        return 0;
    return -1;
}

void Game::startGame()
{
    for (int round = 1; round <= 15; round++)
    {
        cout << "\n==================== Round " << round << " ====================\n";

        for (int i = 0; i < team1.getSize(); i++)
        {
            tahaB *tahaBptr = dynamic_cast<tahaB *>(team1.getHero(i));
            if (tahaBptr != nullptr)
            {
                tahaBptr->applyMarkDamage(&team2);
            }
        }

        for (int i = 0; i < team2.getSize(); i++)
        {
            tahaB *tahaBptr = dynamic_cast<tahaB *>(team2.getHero(i));
            if (tahaBptr != nullptr)
            {
                tahaBptr->applyMarkDamage(&team1);
            }
        }

        for (int i = 0; i < team1.getSize(); i++) // invisiblty for tahaB
        {
            team1.getHero(i)->reduceInvisibleDuration();
        }
        for (int i = 0; i < team2.getSize(); i++)
        {
            team2.getHero(i)->reduceInvisibleDuration();
        }

        for (int i = 0; i < team1.getSize(); i++) // for special ability
        {
            team1.getHero(i)->increaseRage();
        }
        for (int i = 0; i < team2.getSize(); i++)
        {
            team2.getHero(i)->increaseRage();
        }

        for (int i = 0; i < team1.getSize(); i++) // for damage buff
        {
            team1.getHero(i)->decreaseDuration();
        }
        for (int i = 0; i < team2.getSize(); i++)
        {
            team2.getHero(i)->decreaseDuration();
        }

        int energy1 = getEnergyTeam1(round);
        int energy2 = getEnergyTeam2(round);
        cout << "\nTeam 1 *** Energy : " << energy1 << endl;
        cout << "Team 2 *** Energy : " << energy2 << endl;

        teamTurn(team1, team2, energy1);
        int winner = checkWinner();
        if (winner == 1)
        {
            cout << "\n====================" << "\n*** TEAM 1 WINS! ***"
                 << "\n====================";
            return;
        }
        else if (winner == 2)
        {
            cout << "\n====================" << "\n*** TEAM 2 WINS! ***"
                 << "\n====================";
            return;
        }
        else if (winner == 0)
        {
            cout << "\n========================" << "\nDRAW! .. { NO TEAM WINS }"
                 << "\n========================";
            return;
        }

        teamTurn(team2, team1, energy2);
        winner = checkWinner();
        if (winner == 1)
        {
            cout << "\n====================" << "\n*** TEAM 1 WINS! ***"
                 << "\n====================";
            return;
        }
        else if (winner == 2)
        {
            cout << "\n====================" << "\n*** TEAM 2 WINS! ***"
                 << "\n====================";
            return;
        }
        else if (winner == 0)
        {
            cout << "\n========================" << "\nDRAW! .. { NO TEAM WINS }"
                 << "\n========================";
            return;
        }
    }

    cout << "\n==================== END OF 15 ROUNDS ====================\n";

    int alive1 = team1.getAliveCount();
    int alive2 = team2.getAliveCount();

    cout << "\nTeam 1 Alive Heroes : " << alive1 << "\n";
    cout << "Team 2 Alive Heroes : " << alive2 << "\n";

    if (alive1 > alive2)
    {
        cout << "\n====================" << "\n*** TEAM 1 WINS! ***"
             << "\n====================";
    }
    else if (alive2 > alive1)
    {
        cout << "\n====================" << "\n*** TEAM 2 WINS! ***"
             << "\n====================";
    }
    else
    {
        cout << "\n====================" << "\nDRAW! .. { Equal number of heroes alive }"
             << "\n====================";
    }
}

int Game::getEnergyTeam1(int round)
{
    if (round == 1)
        return 5;
    if (round == 2)
        return 8;
    if (round == 3)
        return 9;

    return 10;
}

int Game::getEnergyTeam2(int round)
{
    if (round == 1)
        return 8;
    if (round == 2)
        return 9;

    return 10;
}

void Game::teamTurn(team &currentTeam, team &enemyTeam, int &energy)
{
    int teamNum = (&currentTeam == &team1) ? 1 : 2;
    while (energy > 0)
    {
        cout << "\nTeam " << teamNum << " Turn\n";

        currentTeam.showHeroesWithIndex();

        int heroChoice;
        cout << "\n> Choose Hero : ";
        cin >> heroChoice;

        while (heroChoice < 1 || heroChoice > currentTeam.getSize())
        {
            cout << "\nINVALID HERO! Try again.\n"
                 << "> ";
            cin >> heroChoice;
        }

        hero *Hero = currentTeam.getHero(heroChoice - 1);

        if (Hero->getHp() <= 0)
        {
            cout << "\nThis hero is DEAD! Choose another one.\n";
            continue;
        }

        cout << "\n1. " << left << setw(20) << Hero->getAbilityName(1) << " { Cost : " << Hero->getAbility1Cost() << " }\n";
        cout << "2. " << left << setw(20) << Hero->getAbilityName(2) << " { Cost : " << Hero->getAbility2Cost() << " }\n";
        cout << "3. " << left << setw(20) << Hero->getAbilityName(3) << " { Cost : " << Hero->getSpecialCost() << " }\n";
        cout << "4. END TURN\n";
        int abilityChoice;
        cout << "\n> Choose your ability : ";
        cin >> abilityChoice;

        int cost = 0;
        bool endTurn = false;
        switch (abilityChoice)
        {
        case 1:
            cost = Hero->getAbility1Cost();
            break;
        case 2:
            cost = Hero->getAbility2Cost();
            break;
        case 3:
            if (!Hero->isSpecialReady())
            {
                cout << "\nSPECIAL ABILITY IS NOT READY YET!\n";
                cout << "Need " << Hero->getRageRequired() << " rounds. { Current : "
                     << Hero->getRageCounter() << "/" << Hero->getRageRequired() << " }\n";
                continue;
            }
            cost = Hero->getSpecialCost();
            break;
        case 4:
            cout << "\n"
                 << (teamNum == 1 ? "TEAM 1" : "TEAM 2")
                 << " ENDED THEIR TURN MANUALLY!\n";
            endTurn = true;
            break;
        default:
            cout << "\nINVALID ABILITY!\n";
            continue;
        }

        if (endTurn)
        {
            break;
        }

        if (cost > energy)
        {
            cout << "\nNOT ENOUGH ENERGY!\n";
            continue;
        }

        Hero->abilityMessage(abilityChoice);

        bool fromOwnTeam = Hero->isTargetFromOwnTeam(abilityChoice);
        bool autoTarget = Hero->isAutoTarget(abilityChoice);

        hero *target = nullptr;

        if (!autoTarget)
        {
            if (fromOwnTeam)
            {
                cout << "\n-< YOUR TEAM HEROES >-\n";
                currentTeam.showHeroesWithIndex();

                int targetChoice;
                cout << "\n> Choose a teammate : ";
                cin >> targetChoice;

                while (targetChoice < 1 || targetChoice > currentTeam.getSize())
                {
                    cout << "\nINVALID HERO! Try again.\n";
                    cout << "> ";
                    cin >> targetChoice;
                }

                target = currentTeam.getHero(targetChoice - 1);

                while (target->getHp() <= 0)
                {
                    cout << "\nThis hero is DEAD! Choose another one.\n";
                    cout << "> ";
                    cin >> targetChoice;
                    while (targetChoice < 1 || targetChoice > currentTeam.getSize())
                    {
                        cout << "\nINVALID HERO! Try again.\n";
                        cout << "> ";
                        cin >> targetChoice;
                    }
                    target = currentTeam.getHero(targetChoice - 1);
                }
            }

            else
            {
                cout << "\n-< ENEMY HEROES >-\n";
                enemyTeam.showHeroesWithIndex();

                int targetChoice;
                cout << "\n> Choose an enemy : ";
                cin >> targetChoice;

                while (targetChoice < 1 || targetChoice > enemyTeam.getSize())
                {
                    cout << "\nINVALID HERO! Try again.\n";
                    cout << "> ";
                    cin >> targetChoice;
                }

                target = enemyTeam.getHero(targetChoice - 1);

                while (target->getHp() <= 0)
                {
                    cout << "\nThis hero is DEAD! Choose another one.\n";
                    cout << "> ";
                    cin >> targetChoice;
                    while (targetChoice < 1 || targetChoice > enemyTeam.getSize())
                    {
                        cout << "\nINVALID HERO! Try again.\n";
                        cout << "> ";
                        cin >> targetChoice;
                    }
                    target = enemyTeam.getHero(targetChoice - 1);
                }
            }
        }
        else
        {
            cout << "\n<< Auto-targeting ... >>\n";
        }

        switch (abilityChoice)
        {
        case 1:
            Hero->ability1(target, &currentTeam, &enemyTeam);
            break;
        case 2:
            Hero->ability2(target, &currentTeam, &enemyTeam);
            break;
        case 3:
            Hero->specialAbility(&currentTeam, &enemyTeam);
            Hero->resetRage();
            break;
        }

        if (!autoTarget && target && target->getHp() == 0)
        {
            cout << "\n[!] " << target->getName()
                 << " IS ELIMINATED!\n";
        }

        energy -= cost;

        cout << "\n** Team Remaining Energy : "
             << energy
             << '\n';

        if (energy == 0)
        {
            cout << "\nTeam " << teamNum << " RAN OUT OF ENERGY! TURN ENDS.\n";
        }
    }
}
