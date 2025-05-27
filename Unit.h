#pragma once
#include <iostream>
#include <string>
#include "AbstractGame.h"
#include "BattleField.h"
#include "AbstractRobot.h"
#include "Evolutions.h"
using namespace std;

class Unit
{
private:
    AbstractGame *game;
    vector<int> movementEvolutionOptions = {JUMP_BOT, STEALTH_BOT};
    vector<int> actionEvolutionOptions = {THIRTY_SHOT_BOT, LONG_SHOT_BOT, SEMI_AUTO_BOT};
    vector<int> SeeingEvolutionOptions = {TRACKER_BOT, SCOUT_BOT, BLIND_BOT};
    AbstractRobot *defaultModule;

protected:
    string Type;
    char ID;

public:
    vector<string> messageLog;
    string Name;
    int livesRemaining;
    Battlefield *field;
    Grid *currentGrid;
    AbstractRobot *thinkingModule;
    AbstractRobot *moveModule;
    AbstractRobot *fireModule;
    AbstractRobot *seeingModule;
    Unit *seenUnit;
    bool isRespawning;
    bool canEvolve;
    bool hasMoved;
    bool hasFired;
    bool hasLooked;
    int shellsRemaining;
    int magazineSize;
    Unit(AbstractGame *game, string name);
    bool updatePos(int x, int y);
    vector<int> getEvolutionOptions(); // use this to call for evolution option for your thinking robot
    void evolve(int evolutionOption);
    bool move(int direction);
    bool move(int x, int y);
    bool fire(int x, int y);
    void afterFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y); // call this after using ability of SemiAutoBot/LongShotBot
    Unit *look(int x, int y);
    void destroy();
    void reset();
    void turnReset();
    void log(string message);
};
