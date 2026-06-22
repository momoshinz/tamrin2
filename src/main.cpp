#include "hero.h"
#include "team.h"
#include "doctorWhite.h"
#include "tahaK.h"
#include "tahaB.h"
#include "danny.h"
#include "amin.h"
#include "game.h"
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    srand(time(0));
    
    Game game;
    game.selectHeroes(1);
    game.selectHeroes(2);
    game.startGame();
    
}
