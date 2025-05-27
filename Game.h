#pragma once
#include <iostream>
#include "BattleField.h"
#include "AbstractGame.h"
#include "Unit.h"
#include "Configuration.h"
#include <vector>
using namespace std;

class Game : public AbstractGame
{
public:
    Game(Configuration *config);
    void addToGame(Unit *unit);
    void addToRespawn(Unit *unit);
    void respawnNext();
    void respawnAll();
    void renderBattleField();
    void executeTurn();
    void endTurn();
    void log(string message);
    void runSimulation();
    bool isWinConditionAchieved();
    vector<Unit*> getActiveUnits();
};
