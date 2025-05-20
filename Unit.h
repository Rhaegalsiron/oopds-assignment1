#pragma once

#define JUMP_BOT 0 // Im Redefining it to an integer so its easy to call for 
#define STEALTH_BOT 1// your thinking bot later on
#define THIRTY_SHOT_BOT 2
#define LONG_SHOT_BOT 3
#define SEMI_AUTO_BOT 4
#define TRACKER_BOT 5
#define MAP_VISION_BOT 6

#include <iostream>
#include <string>
#include "BattleField.h"
#include "AbstractGame.h"
#include "AbstractRobot.h"
using namespace std;

class Unit
{

private:
    AbstractGame *game;
    vector<int> movementEvolutionOptions = {JUMP_BOT, STEALTH_BOT};
    vector<int> actionEvolutionOptions = {THIRTY_SHOT_BOT, LONG_SHOT_BOT, SEMI_AUTO_BOT};
    vector<int> SeeingEvolutionOptions = {TRACKER_BOT,MAP_VISION_BOT};
    AbstractRobot *defaultModule;
    AbstractRobot *thinkingModule;
    AbstractRobot *moveModule;
    AbstractRobot *fireModule;
    AbstractRobot *seeingModule;

protected:
    string Type;
    char ID;

public:
    vector<string> messageLog;
    string Name;
    Battlefield *field;
    bool canEvolve;
    bool isInvincible;
    bool isScouting;
    int shellsRemaining;
    int magazineSize;
    int posX;
    int posY;
    Unit(AbstractGame *game, string name, int initialX, int initialY);
    void updatePos(int x, int y);
    vector<int> getEvolutionOptions(); // use this to call for evolution option for your thinking robot
    void evolve(int evolutionOption);
    void move(int direction);
    void move(int x, int y);
    void fire(int x, int y);
    void look(int x, int y);
    void destroy();
    void reset();
};
