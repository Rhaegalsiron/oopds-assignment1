#pragma once
#include <iostream>
#include <string>
#include "AbstractGame.h"
#include "BattleField.h"
#include "GenericRobot.h"
#include "ThinkingRobot.h"
#include "MovingRobot.h"
#include "SeeingRobot.h"
#include "ShootingRobot.h"
using namespace std;

class Unit
{
private:
    AbstractGame *game;
    vector<int> movementEvolutionOptions = {JUMP_BOT, STEALTH_BOT, HAWKING_BOT};
    vector<int> actionEvolutionOptions = {THIRTY_SHOT_BOT, LONG_SHOT_BOT, SEMI_AUTO_BOT, DIZZY_SHOOTER_BOT};
    vector<int> SeeingEvolutionOptions = {TRACKER_BOT, SCOUT_BOT, BLIND_BOT};
    GenericRobot *defaultModule;
    void destroy();

protected:
    string Type;
    char ID;

public:
    vector<string> messageLog;
    string Name;
    int livesRemaining;
    Battlefield *field;
    Grid *currentGrid;
    ThinkingRobot *thinkingModule;
    MovingRobot *moveModule;
    ShootingRobot *fireModule;
    SeeingRobot *seeingModule;
    Unit *seenUnit;
    bool isRespawning;
    bool isStealthed;
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
    void onFiring(Unit *targetUnit, bool isSuccessfulHit, int x, int y); // call this after using ability of SemiAutoBot/LongShotBot
    Unit *look(int x, int y);
    void reset();
    void turnReset();
    void log(string message);
    bool onHit();
    void onMagazineEmpty();
    void renderStatusMessage();
};
