#pragma once
#define GENERIC_ROBOT 0
#define JUMP_BOT 1    // Im Redefining it to an integer so its easy to call for
#define STEALTH_BOT 2 // your thinking bot later on
#define THIRTY_SHOT_BOT 3
#define LONG_SHOT_BOT 4
#define SEMI_AUTO_BOT 5
#define TRACKER_BOT 6
#define SCOUT_BOT 7
#define BLIND_BOT 8
#include <iostream>
#include "Types.h"
using namespace std;

class Unit;

class AbstractRobot
{
protected:
    int hitChance;

public:
    int robot_type;
    virtual bool useAbility() = 0;
    virtual bool useAbility(int x, int y) = 0;
    virtual bool useAbility(Unit *unit) = 0;
    virtual void thinkRobot() = 0;
    virtual bool move(int x, int y) = 0;
    virtual bool fire(int x, int y) = 0;
    virtual bool look(int x, int y) = 0;
};