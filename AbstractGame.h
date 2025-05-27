#pragma once
#include <vector>
#include "BattleField.h"

class AbstractGame
{
protected:
    int simulationSteps;

public:
    vector<string> messageLog;
    vector<Unit *> respawnQueue;
    vector<Unit *> permanentlyEliminated;
    vector<Unit *> units;
    Battlefield *field;
    virtual void addToGame(Unit *unit) = 0;
    virtual void addToRespawn(Unit *unit) = 0;
    virtual void respawnNext() = 0;
    virtual void respawnAll() = 0;
    virtual void renderBattleField() = 0;
    virtual void executeTurn() = 0;
    virtual void endTurn() = 0;
    virtual void log(string message) = 0;
    virtual void runSimulation() = 0;
    virtual bool isWinConditionAchieved() = 0;
    virtual vector<Unit*> getActiveUnits() = 0;
};