#pragma once
#include <iostream>
#include "BattleField.h"
#include "AbstractGame.h"
#include "Unit.h"
#include "Configuration.h"
#include <vector>
#include <fstream>
using namespace std;

class Game : public AbstractGame
{
private:
    ofstream LogFile;

public:
    Game(Configuration *config);
    ~Game();
    string LogFileName;
    void addToGame(Unit *unit);
    void addToRespawn(Unit *unit);
    void respawnNext();
    void respawnAll();
    void renderBattleField();
    void executeTurn();
    void endTurn();
    void log(string message);
    void runSimulation();
    void writeToFile(string message);
    bool isWinConditionAchieved();
    vector<Unit *> getActiveUnits();
};
