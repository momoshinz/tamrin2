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
    hero *getHero(int index);
    int getAliveCount();
};