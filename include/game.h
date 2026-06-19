#pragma once
#include "team.h"
class Game
{
    private:
      team team1;
      team team2;

    public:
      void selectHeroes(int teamNum);
      void startGame();
      int getEnergyTeam1(int round);
      int getEnergyTeam2(int round);
      void teamTurn(team &currentTeam, team &enemyTeam, int &energy);
      int checkWinner();

};