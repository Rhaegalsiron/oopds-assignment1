#pragma once
#define INVALID_POSITION -999999999
#include <iostream>
#include "Types.h"
#include "AbstractRobot.h"
#include "Unit.h"
using namespace std;

class Robot : public AbstractRobot
{
public:
    int robot_type; // make sure this is set to the defined constant of your special bot
    Unit *unit;
};

// All special bots have must have a useAbility function that returns true if the ability is used, and false if the ability cannot be used.
// Override the polymorphic method that is marked virtual for your specific bot.

class MoveBot : public Robot
{
public:
    bool useAbility(Unit *unit) { return false; };
    virtual bool useAbility() = 0;             // for StealthBot
    virtual bool useAbility(int x, int y) = 0; // for JumpBot
    bool move(int x, int y) { return false; };
    bool fire(int x, int y) { return false; };
    bool look(int x, int y) { return false; };
};

class ActionBot : public Robot
{
public:
    bool useAbility() { return false; };
    bool useAbility(Unit *unit) { return false; };
    virtual bool useAbility(int x, int y) = 0; // for LongShotBot and SemiAutoBot
    bool move(int x, int y) { return false; };
    bool fire(int x, int y) { return false; };
    bool look(int x, int y) { return false; };
};

class SeeingBot : public Robot
{
public:
    bool useAbility(int x, int y) { return false; };
    virtual bool useAbility() = 0;           // for MapVisionBot
    virtual bool useAbility(Unit *unit) = 0; // for TrackerBot
    bool move(int x, int y) { return false; };
    bool fire(int x, int y) { return false; };
    bool look(int x, int y) { return false; };
};