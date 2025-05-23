#pragma once
#define JUMP_BOT 0    // Im Redefining it to an integer so its easy to call for
#define STEALTH_BOT 1 // your thinking bot later on
#define THIRTY_SHOT_BOT 2
#define LONG_SHOT_BOT 3
#define SEMI_AUTO_BOT 4
#define TRACKER_BOT 5
#define MAP_VISION_BOT 6
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
    virtual bool move(int x, int y) = 0;
    virtual bool fire(int x, int y) = 0;
    virtual bool look(int x, int y) = 0;
};