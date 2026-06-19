#include "team.h"
#include <iostream>
#include <iomanip>

using namespace std;

void team::addHero(hero *Hero)
{
    heroes.push_back(Hero);
}

void team::showHeroes()
{
    for (hero *Hero : heroes)
    {
        cout << "Hero's Name: "
             << left << setw(20) << Hero->getName()
             << " HP: " << Hero->getHp()
             << endl;
    }
}

hero *team::getHero(int index)
{
    return heroes[index];
}

int team::getSize()
{
    return heroes.size();
}

void team::showHeroesWithIndex()
{
    for (int i = 0; i < heroes.size(); i++)
    {
        cout << i + 1 << ". "
             << left << setw(20)
             << heroes[i]->getName()
             << " HP: "
             << heroes[i]->getHp()
             << endl;
    }
}

void team::removeHero(int index)
{
    heroes.erase(heroes.begin() + index);
}

bool team::gameOver()
{
    return heroes.empty();
}

