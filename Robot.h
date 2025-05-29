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
#define HAWKING_BOT 9
#define DIZZY_SHOOTER_BOT 10
#include <iostream>
#include "Types.h"
using namespace std;

class Unit;

class Robot
{
private:
    Unit *unit;

protected:
    Unit *getUnit();
    void setUnit(Unit *unit);
    int clampToLimit(int currentPos, int targetPos, int limit);

public:
    int robot_type; // make sure this is set to the defined constant of your special bot
};