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
            cout << "\nHERO ALREADY SELECTED!\n~ Try again\n";
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

void Game::startGame()
{
    for (int round = 1; round <= 15; round++)
    {
        cout << "\n==================== Round " << round << " ====================\n";

        int energy1 = getEnergyTeam1(round);
        int energy2 = getEnergyTeam2(round);
        cout << "Team 1 *** Energy: " << energy1 << endl;
        cout << "Team 2 *** Energy: " << energy2 << endl;

        teamTurn(team1, team2, energy1);
        if (team1.gameOver())
        {
            cout << "\n---* TEAM 2 WINS! *---\n";
            return;
        }

        teamTurn(team2, team1, energy2);
        if (team2.gameOver())
        {
            cout << "\n---* TEAM 1 WINS! *---\n";
            return;
        }
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
        return 9;
    if (round == 2)
        return 8;

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

        cout << "\n~ Choose Hero : ";
        cin >> heroChoice;

        while (heroChoice < 1 || heroChoice > currentTeam.getSize())
        {
            cout << "INVALID HERO!\n"
                 << "~ Try again.";
            cin >> heroChoice;
        }

        hero *Hero = currentTeam.getHero(heroChoice - 1);

        cout << "\n1. Ability 1\n";
        cout << "2. Ability 2\n";
        cout << "3. Special Ability\n";

        int abilityChoice;
        cout << "\nChoose your ability : ";
        cin >> abilityChoice;

        int cost = 0;
        switch (abilityChoice)
        {
        case 1:
            cost = Hero->getAbility1Cost();
            break;
        case 2:
            cost = Hero->getAbility2Cost();
            break;
        case 3:
            cost = Hero->getSpecialCost();
            break;
        default:
            cout << "INVALID ABILITY!\n";
            continue;
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
                cout << "\nChoose a teammate : ";
                cin >> targetChoice;
                target = currentTeam.getHero(targetChoice - 1);
            }
            else
            {
                cout << "\n-< ENEMY HEROES >-\n";
                enemyTeam.showHeroesWithIndex();

                int targetChoice;
                cout << "\nChoose an enemy : ";
                cin >> targetChoice;
                target = enemyTeam.getHero(targetChoice - 1);
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
            break;
        }

        if (!autoTarget && target && target->getHp() == 0 && abilityChoice != 2)
        {
            cout << target->getName()
                 << " HAS BEEN ELIMINATED!\n";
        }

        energy -= cost;

        cout << "\n*Team Remaining Energy : "
             << energy
             << '\n';
    }
}