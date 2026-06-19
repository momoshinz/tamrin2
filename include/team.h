#pragma once

#include <vector>
#include "hero.h"

class hero;
class team
{
private:
    std::vector<hero *> heroes;

public:
    void addHero(hero *Hero);
    void showHeroes();
    int getSize();
    void showHeroesWithIndex();
    void removeHero(int index);
    bool gameOver();
    hero *getHero(int index);
};